/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 18:42:57 by abendrih          #+#    #+#             */
/*   Updated: 2025/12/19 18:42:58 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "ray.h"
#include "render.h"
#include <float.h>

// t_hit	get_hit_at_pixel(t_scene *scene, int x, int y)
// {
// 	t_ray	ray;
// 	t_hit	hit;

// 	ray = get_camera_ray(&scene->camera, x, y);
// 	hit.hit = false;
// 	hit.t = DBL_MAX;
// 	hit.obj_type = OBJ_NONE;
// 	hit.object = NULL;
// 	return (hit);
// }

void	select_object(t_scene *scene, int x, int y)
{
	t_ray	ray;
	t_hit	hit;

	ray = get_camera_ray(&scene->camera, x, y);
	hit = trace_ray_select(ray, scene);
	if (hit.hit && hit.object)
	{
		scene->selection.type = hit.obj_type;
		scene->selection.object = hit.object;
	}
	else
	{
		scene->selection.type = OBJ_NONE;
		scene->selection.object = NULL;
	}
}

void	deselect_object(t_scene *scene)
{
	scene->selection.type = OBJ_NONE;
	scene->selection.object = NULL;
}
