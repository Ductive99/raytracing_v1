/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_buttons.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 00:00:00 by abendrih          #+#    #+#             */
/*   Updated: 2025/12/19 18:27:44 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hud_internal.h"

void	hud_init_button(int idx, int x, int y, int action, char *label)
{
	g_buttons[idx].x = x;
	g_buttons[idx].y = y;
	g_buttons[idx].w = 40;
	g_buttons[idx].h = 25;
	g_buttons[idx].action = action;
	g_buttons[idx].label = label;
}

void	hud_init_buttons(void)
{
	int	bx;
	int	by;
	int	cx;

	bx = HUD_X + 35;
	by = HUD_Y + 90;
	hud_init_button(0, bx, by, BTN_MOVE_LEFT, "<");
	hud_init_button(1, bx + 50, by, BTN_MOVE_RIGHT, ">");
	hud_init_button(2, bx + 110, by, BTN_MOVE_FWD, "^");
	hud_init_button(3, bx + 160, by, BTN_MOVE_BACK, "v");
	by += 35;
	hud_init_button(4, bx + 50, by, BTN_MOVE_UP, "W");
	hud_init_button(5, bx + 110, by, BTN_MOVE_DOWN, "S");
	by = HUD_Y + 200;
	hud_init_button(6, bx, by, BTN_ROT_LEFT, "A");
	hud_init_button(7, bx + 50, by, BTN_ROT_RIGHT, "D");
	hud_init_button(8, bx + 110, by, BTN_ROT_UP, "Q");
	hud_init_button(9, bx + 160, by, BTN_ROT_DOWN, "E");
	by = HUD_Y + 290;
	hud_init_button(10, bx + 50, by, BTN_SIZE_UP, "+");
	hud_init_button(11, bx + 110, by, BTN_SIZE_DOWN, "-");
	cx = HUD_X + (HUD_W - 100) / 2;
	by = HUD_Y + 380;
	hud_init_button(12, cx, by, BTN_DESELECT, "DESELECT");
	g_buttons[12].w = 100;
	by = HUD_Y + 420;
	hud_init_button(13, cx, by, BTN_QUIT, "QUIT");
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
			hud_draw_rect(&mlx->img, g_light_btns[i].x - 2, g_light_btns[i].y
				- 2, g_light_btns[i].w + 4, g_light_btns[i].h + 4, 0xFFAA00);
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
