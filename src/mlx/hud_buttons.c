/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_buttons.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 00:00:00 by abendrih          #+#    #+#             */
/*   Updated: 2025/12/19 19:50:43 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hud_internal.h"

static void	hud_init_button(int idx, t_rect pos, int action, char *label)
{
	g_buttons[idx].x = pos.x;
	g_buttons[idx].y = pos.y;
	g_buttons[idx].w = 40;
	g_buttons[idx].h = 25;
	g_buttons[idx].action = action;
	g_buttons[idx].label = label;
}

static void	hud_init_buttons_move(int bx, int by)
{
	hud_init_button(0, (t_rect){bx, by, 0, 0}, BTN_MOVE_LEFT, "<");
	hud_init_button(1, (t_rect){bx + 50, by, 0, 0}, BTN_MOVE_RIGHT, ">");
	hud_init_button(2, (t_rect){bx + 110, by, 0, 0}, BTN_MOVE_FWD, "^");
	hud_init_button(3, (t_rect){bx + 160, by, 0, 0}, BTN_MOVE_BACK, "v");
	hud_init_button(4, (t_rect){bx + 50, by + 35, 0, 0}, BTN_MOVE_UP, "W");
	hud_init_button(5, (t_rect){bx + 110, by + 35, 0, 0}, BTN_MOVE_DOWN, "S");
}

static void	hud_init_buttons_rot(int bx, int by)
{
	hud_init_button(6, (t_rect){bx, by, 0, 0}, BTN_ROT_LEFT, "A");
	hud_init_button(7, (t_rect){bx + 50, by, 0, 0}, BTN_ROT_RIGHT, "D");
	hud_init_button(8, (t_rect){bx + 110, by, 0, 0}, BTN_ROT_UP, "Q");
	hud_init_button(9, (t_rect){bx + 160, by, 0, 0}, BTN_ROT_DOWN, "E");
}

void	hud_init_buttons(void)
{
	int	bx;
	int	cx;

	bx = HUD_X + 35;
	cx = HUD_X + (HUD_W - 100) / 2;
	hud_init_buttons_move(bx, HUD_Y + 90);
	hud_init_buttons_rot(bx, HUD_Y + 200);
	hud_init_button(10, (t_rect){bx + 50, HUD_Y + 290, 0, 0}, BTN_SIZE_UP, "+");
	hud_init_button(11, (t_rect){bx + 110, HUD_Y + 290, 0, 0}, BTN_SIZE_DOWN,
		"-");
	hud_init_button(12, (t_rect){cx, HUD_Y + 380, 0, 0}, BTN_DESELECT,
		"DESELECT");
	g_buttons[12].w = 100;
	hud_init_button(13, (t_rect){cx, HUD_Y + 420, 0, 0}, BTN_QUIT, "QUIT");
	g_buttons[13].w = 100;
}

void	hud_draw_btn_labels(t_mlx *mlx)
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

void	hud_draw_all_buttons(t_mlx *mlx)
{
	int	i;

	i = 0;
	while (i < NUM_BUTTONS)
	{
		hud_draw_button(mlx, &g_buttons[i]);
		i++;
	}
}

void	hud_draw_light_buttons(t_mlx *mlx, t_scene *scene)
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
			hud_draw_rect(&mlx->img, (t_rect){g_light_btns[i].x - 2,
				g_light_btns[i].y - 2, g_light_btns[i].w + 4, g_light_btns[i].h
				+ 4}, 0xFFAA00);
		hud_draw_button(mlx, &g_light_btns[i]);
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
