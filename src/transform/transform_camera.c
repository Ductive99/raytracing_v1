/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_camera.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 00:00:00 by abendrih          #+#    #+#             */
/*   Updated: 2025/12/19 18:58:55 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vector_math.h"
#include <math.h>

static t_vec3	get_cam_right(t_vec3 forward)
{
	t_vec3	world_up;

	world_up = (t_vec3){0, 1, 0};
	if (fabs(forward.y) > 0.999)
		world_up = (t_vec3){0, 0, 1};
	return (vec_normalize(vec_cross(forward, world_up)));
}

t_vec3	get_camera_delta(t_cam *cam, t_vec3 local_delta)
{
	t_vec3	right;
	t_vec3	up;
	t_vec3	result;

	right = get_cam_right(cam->dir);
	up = vec_normalize(vec_cross(right, cam->dir));
	result = vec_scale(local_delta.x, right);
	result = vec_add(result, vec_scale(local_delta.y, up));
	result = vec_add(result, vec_scale(local_delta.z, cam->dir));
	return (result);
}

void	translate_camera(t_scene *scene, t_vec3 delta)
{
	scene->camera.position = vec_add(scene->camera.position, delta);
}

void	rotate_camera(t_scene *scene, t_vec3 axis, double angle)
{
	scene->camera.dir = rotate_vec(scene->camera.dir, axis, angle);
}
