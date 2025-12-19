/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 00:00:00 by abendrih          #+#    #+#             */
/*   Updated: 2025/12/19 21:12:37 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hud_internal.h"

static void	hud_init_button(t_button *btn, t_rect pos, int action, char *label)
{
	btn->x = pos.x;
	btn->y = pos.y;
	btn->w = 40;
	btn->h = 25;
	btn->action = action;
	btn->label = label;
}

static void	hud_init_buttons_move(t_mlx *mlx, int bx, int by)
{
	hud_init_button(&mlx->hud.buttons[0], (t_rect){bx, by, 0, 0},
		BTN_MOVE_LEFT, "<");
	hud_init_button(&mlx->hud.buttons[1], (t_rect){bx + 50, by, 0, 0},
		BTN_MOVE_RIGHT, ">");
	hud_init_button(&mlx->hud.buttons[2], (t_rect){bx + 110, by, 0, 0},
		BTN_MOVE_FWD, "^");
	hud_init_button(&mlx->hud.buttons[3], (t_rect){bx + 160, by, 0, 0},
		BTN_MOVE_BACK, "v");
	hud_init_button(&mlx->hud.buttons[4], (t_rect){bx + 50, by + 35, 0, 0},
		BTN_MOVE_UP, "W");
	hud_init_button(&mlx->hud.buttons[5], (t_rect){bx + 110, by + 35, 0, 0},
		BTN_MOVE_DOWN, "S");
}

static void	hud_init_buttons_rot(t_mlx *mlx, int bx, int by)
{
	hud_init_button(&mlx->hud.buttons[6], (t_rect){bx, by, 0, 0},
		BTN_ROT_LEFT, "A");
	hud_init_button(&mlx->hud.buttons[7], (t_rect){bx + 50, by, 0, 0},
		BTN_ROT_RIGHT, "D");
	hud_init_button(&mlx->hud.buttons[8], (t_rect){bx + 110, by, 0, 0},
		BTN_ROT_UP, "Q");
	hud_init_button(&mlx->hud.buttons[9], (t_rect){bx + 160, by, 0, 0},
		BTN_ROT_DOWN, "E");
}

void	hud_init_buttons(t_mlx *mlx)
{
	int	bx;
	int	cx;

	bx = HUD_X + 35;
	cx = HUD_X + (HUD_W - 100) / 2;
	hud_init_buttons_move(mlx, bx, HUD_Y + 90);
	hud_init_buttons_rot(mlx, bx, HUD_Y + 200);
	hud_init_button(&mlx->hud.buttons[10], (t_rect){bx + 50, HUD_Y + 290, 0, 0},
		BTN_SIZE_UP, "+");
	hud_init_button(&mlx->hud.buttons[11], (t_rect){bx + 110, HUD_Y + 290, 0,
		0}, BTN_SIZE_DOWN, "-");
	hud_init_button(&mlx->hud.buttons[12], (t_rect){cx, HUD_Y + 380, 0, 0},
		BTN_DESELECT, "DESELECT");
	mlx->hud.buttons[12].w = 100;
	hud_init_button(&mlx->hud.buttons[13], (t_rect){cx, HUD_Y + 420, 0, 0},
		BTN_QUIT, "QUIT");
	mlx->hud.buttons[13].w = 100;
}
