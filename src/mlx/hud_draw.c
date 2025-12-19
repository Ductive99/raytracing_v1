/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 00:00:00 by abendrih          #+#    #+#             */
/*   Updated: 2025/12/19 18:27:44 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hud_internal.h"

void	hud_draw_rect(t_img *img, int x, int y, int w, int h, int color)
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

void	hud_draw_border(t_img *img, int x, int y, int w, int h, int color)
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
	hud_draw_border(&mlx->img, HUD_X, HUD_Y, HUD_W, HUD_H, 0xFF00FF);
	hud_draw_border(&mlx->img, HUD_X + 1, HUD_Y + 1, HUD_W - 2, HUD_H - 2,
		0xCC00CC);
	hud_draw_border(&mlx->img, HUD_X + 2, HUD_Y + 2, HUD_W - 4, HUD_H - 4,
		0x660066);
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
	int	bg;
	int	border;

	bg = 0x1a0a1a;
	border = 0xFF00FF;
	hud_draw_rect(&mlx->img, btn->x, btn->y, btn->w, btn->h, bg);
	hud_draw_border(&mlx->img, btn->x, btn->y, btn->w, btn->h, border);
	hud_draw_border(&mlx->img, btn->x + 1, btn->y + 1, btn->w - 2, btn->h - 2,
		border);
}
