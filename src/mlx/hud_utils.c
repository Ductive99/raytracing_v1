/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 00:00:00 by abendrih          #+#    #+#             */
/*   Updated: 2025/12/19 21:12:37 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hud_internal.h"

void	hud_count_lights(t_mlx *mlx, t_scene *scene)
{
	t_list	*lst;
	int		i;

	i = 0;
	lst = scene->lights;
	while (lst && i < MAX_LIGHTS)
	{
		mlx->hud.light_btns[i].x = HUD_X + 35;
		mlx->hud.light_btns[i].y = HUD_Y + 480 + i * 30;
		mlx->hud.light_btns[i].w = 80;
		mlx->hud.light_btns[i].h = 25;
		mlx->hud.light_btns[i].action = BTN_LIGHT_BASE + i;
		mlx->hud.light_btns[i].label = "Light X";
		lst = lst->next;
		i++;
	}
	mlx->hud.num_lights = i;
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
