/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 00:00:00 by abendrih          #+#    #+#             */
/*   Updated: 2025/12/19 18:55:03 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hud_internal.h"

t_button	g_buttons[NUM_BUTTONS];
t_button	g_light_btns[MAX_LIGHTS];
int			g_num_lights = 0;

void	hud_count_lights(t_scene *scene)
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

void	hud_select_light_by_idx(t_scene *scene, int idx)
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

char	*hud_get_selection_name(t_scene *scene)
{
	if (scene->selection.type == OBJ_SPHERE)
		return ("Sphere");
	else if (scene->selection.type == OBJ_PLANE)
		return ("Plane");
	else if (scene->selection.type == OBJ_CYLINDER)
		return ("Cylinder");
	else if (scene->selection.type == OBJ_CONE)
		return ("Cone");
	else if (scene->selection.type == OBJ_LIGHT)
		return ("Light");
	else if (scene->selection.type == OBJ_CAMERA)
		return ("Camera");
	return ("None");
}

void	rotate_hud(t_scene *scene, t_vec3 axis, double angle)
{
	if (scene->selection.type != OBJ_NONE)
		rotate_selection(scene, axis, angle);
	else
		rotate_camera(scene, axis, angle);
}

void	draw_hud(t_mlx *mlx, t_scene *scene)
{
	static int	init = 0;
	char		*sel_name;
	int			color;

	if (!init)
	{
		hud_init_buttons();
		hud_count_lights(scene);
		init = 1;
	}
	hud_draw_panel_bg(mlx);
	hud_draw_all_buttons(mlx);
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, HUD_X + 85, HUD_Y + 25, 0xFF00FF,
		"[ miniRT ]");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, HUD_X + 95, HUD_Y + 45, 0xFF88FF,
		"CONTROLS");
	hud_draw_section(mlx, HUD_Y + 70, "MOVE");
	hud_draw_section(mlx, HUD_Y + 180, "ROTATE");
	hud_draw_section(mlx, HUD_Y + 270, "SIZE");
	hud_draw_section(mlx, HUD_Y + 330, "SELECTED");
	hud_draw_section(mlx, HUD_Y + 460, "LIGHTS");
	hud_draw_light_buttons(mlx, scene);
	hud_draw_btn_labels(mlx);
	sel_name = hud_get_selection_name(scene);
	if (scene->selection.type != OBJ_NONE)
		color = 0xFF8800;
	else
		color = 0x00FFAA;
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, HUD_X + 95, HUD_Y + 355, color,
		sel_name);
}
