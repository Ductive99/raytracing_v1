/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 00:00:00 by abendrih          #+#    #+#             */
/*   Updated: 2025/12/18 11:27:09 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_button	g_buttons[NUM_BUTTONS];
static t_button	g_light_btns[MAX_LIGHTS];
static int		g_num_lights = 0;

static void	draw_rect(t_img *img, int x, int y, int w, int h, int color)
{
	int	i;
	int	j;

	j = 0;
	while (j < h)
	{
		i = 0;
		while (i < w)
		{
			put_pixel(img, x + i, y + j, color);
			i++;
		}
		j++;
	}
}

static void	draw_border(t_img *img, int x, int y, int w, int h, int color)
{
	int	i;

	i = 0;
	while (i < w)
	{
		put_pixel(img, x + i, y, color);
		put_pixel(img, x + i, y + h - 1, color);
		i++;
	}
	i = 0;
	while (i < h)
	{
		put_pixel(img, x, y + i, color);
		put_pixel(img, x + w - 1, y + i, color);
		i++;
	}
}

static void	init_button(int idx, int x, int y, int action, char *label)
{
	g_buttons[idx].x = x;
	g_buttons[idx].y = y;
	g_buttons[idx].w = 40;
	g_buttons[idx].h = 25;
	g_buttons[idx].action = action;
	g_buttons[idx].label = label;
}

static void	init_buttons(void)
{
	int	bx;
	int	by;
	int	cx;

	bx = HUD_X + 35;
	by = HUD_Y + 90;
	init_button(0, bx, by, BTN_MOVE_LEFT, "<");
	init_button(1, bx + 50, by, BTN_MOVE_RIGHT, ">");
	init_button(2, bx + 110, by, BTN_MOVE_FWD, "^");
	init_button(3, bx + 160, by, BTN_MOVE_BACK, "v");
	by += 35;
	init_button(4, bx + 50, by, BTN_MOVE_UP, "W");
	init_button(5, bx + 110, by, BTN_MOVE_DOWN, "S");
	by = HUD_Y + 200;
	init_button(6, bx, by, BTN_ROT_LEFT, "A");
	init_button(7, bx + 50, by, BTN_ROT_RIGHT, "D");
	init_button(8, bx + 110, by, BTN_ROT_UP, "Q");
	init_button(9, bx + 160, by, BTN_ROT_DOWN, "E");
	by = HUD_Y + 290;
	init_button(10, bx + 50, by, BTN_SIZE_UP, "+");
	init_button(11, bx + 110, by, BTN_SIZE_DOWN, "-");
	cx = HUD_X + (HUD_W - 100) / 2;
	by = HUD_Y + 380;
	init_button(12, cx, by, BTN_DESELECT, "DESELECT");
	g_buttons[12].w = 100;
	by = HUD_Y + 420;
	init_button(13, cx, by, BTN_QUIT, "QUIT");
	g_buttons[13].w = 100;
}

static void	count_lights(t_scene *scene)
{
	t_list	*lst;
	int		i;

	i = 0;
	lst = scene->lights;
	while (lst && i < MAX_LIGHTS)
	{
		g_light_btns[i].x = HUD_X + 35;
		g_light_btns[i].y = HUD_Y + 480 + i * 30;
		g_light_btns[i].w = 80;
		g_light_btns[i].h = 25;
		g_light_btns[i].action = BTN_LIGHT_BASE + i;
		g_light_btns[i].label = "Light X";
		lst = lst->next;
		i++;
	}
	g_num_lights = i;
}

static void	draw_button(t_mlx *mlx, t_button *btn)
{
	int	bg;
	int	border;

	bg = 0x1a0a1a;
	border = 0xFF00FF;
	draw_rect(&mlx->img, btn->x, btn->y, btn->w, btn->h, bg);
	draw_border(&mlx->img, btn->x, btn->y, btn->w, btn->h, border);
	draw_border(&mlx->img, btn->x + 1, btn->y + 1, btn->w - 2, btn->h - 2,
		border);
}

static void	draw_btn_labels(t_mlx *mlx)
{
	int	i;
	int	offset_x;
	int	text_len;

	i = 0;
	while (i < NUM_BUTTONS)
	{
		text_len = ft_strlen(g_buttons[i].label) * 6;
		offset_x = (g_buttons[i].w - text_len) / 2;
		if (offset_x < 4)
			offset_x = 4;
		mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, g_buttons[i].x + offset_x,
			g_buttons[i].y + 17, 0xFF88FF, g_buttons[i].label);
		i++;
	}
}

static void	draw_panel_bg(t_mlx *mlx)
{
	int	x;
	int	y;

	y = HUD_Y;
	while (y < HUD_Y + HUD_H)
	{
		x = HUD_X;
		while (x < HUD_X + HUD_W)
		{
			put_pixel(&mlx->img, x, y, 0x0D0510);
			x++;
		}
		y++;
	}
	draw_border(&mlx->img, HUD_X, HUD_Y, HUD_W, HUD_H, 0xFF00FF);
	draw_border(&mlx->img, HUD_X + 1, HUD_Y + 1, HUD_W - 2, HUD_H - 2,
		0xCC00CC);
	draw_border(&mlx->img, HUD_X + 2, HUD_Y + 2, HUD_W - 4, HUD_H - 4,
		0x660066);
}

static void	draw_section(t_mlx *mlx, int y, char *title)
{
	int	x;

	x = HUD_X + 15;
	while (x < HUD_X + HUD_W - 15)
	{
		put_pixel(&mlx->img, x, y + 5, 0x660066);
		x++;
	}
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, HUD_X + 100, y, 0xFF66FF, title);
}

static void	draw_all_buttons(t_mlx *mlx)
{
	int	i;

	i = 0;
	while (i < NUM_BUTTONS)
	{
		draw_button(mlx, &g_buttons[i]);
		i++;
	}
}

static void	draw_light_buttons(t_mlx *mlx, t_scene *scene)
{
	int		i;
	int		sel;
	t_list	*lst;
	char	num[2];

	i = 0;
	lst = scene->lights;
	while (i < g_num_lights)
	{
		sel = (scene->selection.type == OBJ_LIGHT
				&& scene->selection.object == lst->obj);
		if (sel)
			draw_rect(&mlx->img, g_light_btns[i].x - 2, g_light_btns[i].y - 2,
				g_light_btns[i].w + 4, g_light_btns[i].h + 4, 0xFFAA00);
		draw_button(mlx, &g_light_btns[i]);
		num[0] = '1' + i;
		num[1] = '\0';
		mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, g_light_btns[i].x + 10,
			g_light_btns[i].y + 17, 0xFF88FF, "Light");
		mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, g_light_btns[i].x + 50,
			g_light_btns[i].y + 17, 0xFF88FF, num);
		lst = lst->next;
		i++;
	}
}

static char	*get_selection_name(t_scene *scene)
{
	if (scene->selection.type == OBJ_SPHERE)
		return ("Sphere");
	else if (scene->selection.type == OBJ_PLANE)
		return ("Plane");
	else if (scene->selection.type == OBJ_CYLINDER)
		return ("Cylinder");
	else if (scene->selection.type == OBJ_LIGHT)
		return ("Light");
	else if (scene->selection.type == OBJ_CAMERA)
		return ("Camera");
	return ("None");
}

void	draw_hud(t_mlx *mlx, t_scene *scene)
{
	static int	init = 0;
	char		*sel_name;
	int			color;

	if (!init)
	{
		init_buttons();
		count_lights(scene);
		init = 1;
	}
	draw_panel_bg(mlx);
	draw_all_buttons(mlx);
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, HUD_X + 85, HUD_Y + 25, 0xFF00FF,
		"[ miniRT ]");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, HUD_X + 95, HUD_Y + 45, 0xFF88FF,
		"CONTROLS");
	draw_section(mlx, HUD_Y + 70, "MOVE");
	draw_section(mlx, HUD_Y + 180, "ROTATE");
	draw_section(mlx, HUD_Y + 270, "SIZE");
	draw_section(mlx, HUD_Y + 330, "SELECTED");
	draw_section(mlx, HUD_Y + 460, "LIGHTS");
	draw_light_buttons(mlx, scene);
	draw_btn_labels(mlx);
	sel_name = get_selection_name(scene);
	if (scene->selection.type != OBJ_NONE)
		color = 0xFF8800;
	else
		color = 0x00FFAA;
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, HUD_X + 95, HUD_Y + 355, color,
		sel_name);
}

void	rotate_hud(t_scene *scene, t_vec3 axis, double angle)
{
	if (scene->selection.type != OBJ_NONE)
		rotate_selection(scene, axis, angle);
	else
		rotate_camera(scene, axis, angle);
}

static int	do_move(t_scene *scene, int action)
{
	t_vec3	delta;

	delta = (t_vec3){0, 0, 0};
	if (action == BTN_MOVE_LEFT)
		delta.x = -MOVE_SPEED;
	else if (action == BTN_MOVE_RIGHT)
		delta.x = MOVE_SPEED;
	else if (action == BTN_MOVE_FWD)
		delta.z = MOVE_SPEED;
	else if (action == BTN_MOVE_BACK)
		delta.z = -MOVE_SPEED;
	else if (action == BTN_MOVE_UP)
		delta.y = MOVE_SPEED;
	else if (action == BTN_MOVE_DOWN)
		delta.y = -MOVE_SPEED;
	else
		return (0);
	if (scene->selection.type != OBJ_NONE)
		translate_selection(scene, delta);
	else
		translate_camera(scene, delta);
	return (1);
}

static int	do_rotate(t_scene *scene, int action)
{
	if (action == BTN_ROT_LEFT)
		rotate_hud(scene, (t_vec3){0, 1, 0}, ROTATE_SPEED);
	else if (action == BTN_ROT_RIGHT)
		rotate_hud(scene, (t_vec3){0, 1, 0}, -ROTATE_SPEED);
	else if (action == BTN_ROT_UP)
		rotate_hud(scene, (t_vec3){1, 0, 0}, ROTATE_SPEED);
	else if (action == BTN_ROT_DOWN)
		rotate_hud(scene, (t_vec3){1, 0, 0}, -ROTATE_SPEED);
	else
		return (0);
	return (1);
}

static int	do_other(t_scene *scene, int action)
{
	if (action == BTN_SIZE_UP)
		resize_selection(scene, 1.0 + RESIZE_SPEED);
	else if (action == BTN_SIZE_DOWN)
		resize_selection(scene, 1.0 - RESIZE_SPEED);
	else if (action == BTN_DESELECT)
		deselect_object(scene);
	else if (action == BTN_QUIT)
		return (2);
	else
		return (0);
	return (1);
}

static void	select_light_by_idx(t_scene *scene, int idx)
{
	t_list	*lst;
	int		i;

	lst = scene->lights;
	i = 0;
	while (lst && i < idx)
	{
		lst = lst->next;
		i++;
	}
	if (lst)
	{
		scene->selection.type = OBJ_LIGHT;
		scene->selection.object = lst->obj;
	}
}

static int	check_light_click(int x, int y, t_scene *scene)
{
	int	i;

	i = 0;
	while (i < g_num_lights)
	{
		if (x >= g_light_btns[i].x && x < g_light_btns[i].x + g_light_btns[i].w
			&& y >= g_light_btns[i].y && y < g_light_btns[i].y
			+ g_light_btns[i].h)
		{
			select_light_by_idx(scene, i);
			return (1);
		}
		i++;
	}
	return (0);
}

int	handle_hud_click(int x, int y, t_scene *scene)
{
	int	i;
	int	act;
	int	ret;

	if (check_light_click(x, y, scene))
		return (1);
	i = 0;
	while (i < NUM_BUTTONS)
	{
		if (x >= g_buttons[i].x && x < g_buttons[i].x + g_buttons[i].w
			&& y >= g_buttons[i].y && y < g_buttons[i].y + g_buttons[i].h)
		{
			act = g_buttons[i].action;
			ret = do_move(scene, act);
			if (ret)
				return (ret);
			ret = do_rotate(scene, act);
			if (ret)
				return (ret);
			return (do_other(scene, act));
		}
		i++;
	}
	return (0);
}
