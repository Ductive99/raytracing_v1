/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 00:00:00 by abendrih          #+#    #+#             */
/*   Updated: 2025/12/19 21:12:37 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hud_internal.h"

static void	draw_hud_titles(t_mlx *mlx)
{
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, HUD_X + 85, HUD_Y + 25, 0xFF00FF,
		"[ miniRT ]");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, HUD_X + 95, HUD_Y + 45, 0xFF88FF,
		"CONTROLS");
	hud_draw_section(mlx, HUD_Y + 70, "MOVE");
	hud_draw_section(mlx, HUD_Y + 180, "ROTATE");
	hud_draw_section(mlx, HUD_Y + 270, "SIZE");
	hud_draw_section(mlx, HUD_Y + 330, "SELECTED");
	hud_draw_section(mlx, HUD_Y + 460, "LIGHTS");
}

static void	draw_hud_selection(t_mlx *mlx, t_scene *scene)
{
	char	*sel_name;
	int		color;

	sel_name = hud_get_selection_name(scene);
	color = 0x00FFAA;
	if (scene->selection.type != OBJ_NONE)
		color = 0xFF8800;
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, HUD_X + 95, HUD_Y + 355, color,
		sel_name);
}

void	draw_hud(t_mlx *mlx, t_scene *scene)
{
	if (!mlx->hud.initialized)
	{
		hud_init_buttons(mlx);
		hud_count_lights(mlx, scene);
		mlx->hud.initialized = 1;
	}
	hud_draw_panel_bg(mlx);
	hud_draw_all_buttons(mlx);
	draw_hud_titles(mlx);
	hud_draw_light_buttons(mlx, scene);
	hud_draw_btn_labels(mlx);
	draw_hud_selection(mlx, scene);
}
