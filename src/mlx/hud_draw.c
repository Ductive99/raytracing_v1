/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 00:00:00 by abendrih          #+#    #+#             */
/*   Updated: 2025/12/19 19:48:52 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hud_internal.h"

void	hud_draw_rect(t_img *img, t_rect r, int color)
{
	int	i;
	int	j;

	j = 0;
	while (j < r.h)
	{
		i = 0;
		while (i < r.w)
		{
			put_pixel(img, r.x + i, r.y + j, color);
			i++;
		}
		j++;
	}
}

void	hud_draw_border(t_img *img, t_rect r, int color)
{
	int	i;

	i = 0;
	while (i < r.w)
	{
		put_pixel(img, r.x + i, r.y, color);
		put_pixel(img, r.x + i, r.y + r.h - 1, color);
		i++;
	}
	i = 0;
	while (i < r.h)
	{
		put_pixel(img, r.x, r.y + i, color);
		put_pixel(img, r.x + r.w - 1, r.y + i, color);
		i++;
	}
}

void	hud_draw_panel_bg(t_mlx *mlx)
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
	hud_draw_border(&mlx->img, (t_rect){HUD_X, HUD_Y, HUD_W, HUD_H}, 0xFF00FF);
	hud_draw_border(&mlx->img, (t_rect){HUD_X + 1, HUD_Y + 1, HUD_W - 2, HUD_H
		- 2}, 0xCC00CC);
	hud_draw_border(&mlx->img, (t_rect){HUD_X + 2, HUD_Y + 2, HUD_W - 4, HUD_H
		- 4}, 0x660066);
}

void	hud_draw_section(t_mlx *mlx, int y, char *title)
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

void	hud_draw_button(t_mlx *mlx, t_button *btn)
{
	int		bg;
	int		border;
	t_rect	r;

	bg = 0x1a0a1a;
	border = 0xFF00FF;
	r = (t_rect){btn->x, btn->y, btn->w, btn->h};
	hud_draw_rect(&mlx->img, r, bg);
	hud_draw_border(&mlx->img, r, border);
	hud_draw_border(&mlx->img, (t_rect){btn->x + 1, btn->y + 1, btn->w - 2,
		btn->h - 2}, border);
}
