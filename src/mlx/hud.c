/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 00:00:00 by abendrih          #+#    #+#             */
/*   Updated: 2025/12/18 08:29:52 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	draw_help_line(t_mlx *mlx, int y, char *text)
{
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, WIDTH - 250, y, 0xFFFFFF, text);
}

void	draw_hud(t_mlx *mlx, t_scene *scene)
{
	int		y;
	char	*mode;

	y = 30;
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, WIDTH - 250, y, 0x00FF00,
		"=== CONTROLS ===");
	y += 25;
	draw_help_line(mlx, y, "--- MOVEMENT ---");
	y += 20;
	draw_help_line(mlx, y, "Arrows : Move X/Z");
	y += 20;
	draw_help_line(mlx, y, "W/S    : Move Y");
	y += 25;
	draw_help_line(mlx, y, "--- ROTATION ---");
	y += 20;
	draw_help_line(mlx, y, "A/D    : Rotate Y axis");
	y += 20;
	draw_help_line(mlx, y, "Q/E    : Rotate X axis");
	y += 25;
	draw_help_line(mlx, y, "--- RESIZE ---");
	y += 20;
	draw_help_line(mlx, y, "+/-    : Scale object");
	y += 25;
	draw_help_line(mlx, y, "--- SELECTION ---");
	y += 20;
	draw_help_line(mlx, y, "L-Click: Select object");
	y += 20;
	draw_help_line(mlx, y, "R-Click: Deselect");
	y += 20;
	draw_help_line(mlx, y, "R      : Deselect");
	y += 25;
	draw_help_line(mlx, y, "ESC    : Quit");
	y += 30;
	if (scene->selection.type != OBJ_NONE)
		mode = "OBJECT";
	else
		mode = "CAMERA";
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, WIDTH - 250, y, 0xFFFF00,
		"Mode:");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, WIDTH - 190, y, 0x00FFFF, mode);
}
