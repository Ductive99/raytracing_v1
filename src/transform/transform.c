/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 00:00:00 by abendrih          #+#    #+#             */
/*   Updated: 2025/12/19 00:00:00 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vector_math.h"
#include <math.h>

t_vec3	rotate_vec(t_vec3 v, t_vec3 axis, double angle)
{
	double	cos_a;
	double	sin_a;
	t_vec3	result;
	double	dot;

	angle = angle * M_PI / 180.0;
	cos_a = cos(angle);
	sin_a = sin(angle);
	axis = vec_normalize(axis);
	dot = vec_dot(v, axis);
	result.x = v.x * cos_a + (axis.y * v.z - axis.z * v.y) * sin_a + axis.x
		* dot * (1 - cos_a);
	result.y = v.y * cos_a + (axis.z * v.x - axis.x * v.z) * sin_a + axis.y
		* dot * (1 - cos_a);
	result.z = v.z * cos_a + (axis.x * v.y - axis.y * v.x) * sin_a + axis.z
		* dot * (1 - cos_a);
	return (vec_normalize(result));
}

void	translate_selection(t_scene *scene, t_vec3 delta)
{
	if (scene->selection.type == OBJ_NONE || !scene->selection.object)
		return ;
	if (scene->selection.type == OBJ_SPHERE)
		translate_sphere((t_sphere *)scene->selection.object, delta);
	else if (scene->selection.type == OBJ_PLANE)
		translate_plane((t_plan *)scene->selection.object, delta);
	else if (scene->selection.type == OBJ_CYLINDER)
		translate_cylinder((t_cylinder *)scene->selection.object, delta);
	else if (scene->selection.type == OBJ_CONE)
		translate_cone((t_cone *)scene->selection.object, delta);
	else if (scene->selection.type == OBJ_LIGHT)
		translate_light((t_light *)scene->selection.object, delta);
	else if (scene->selection.type == OBJ_CAMERA)
		translate_camera(scene, delta);
}

void	rotate_selection(t_scene *scene, t_vec3 axis, double angle)
{
	if (scene->selection.type == OBJ_NONE || !scene->selection.object)
		return ;
	if (scene->selection.type == OBJ_PLANE)
		rotate_plane((t_plan *)scene->selection.object, axis, angle);
	else if (scene->selection.type == OBJ_CYLINDER)
		rotate_cylinder((t_cylinder *)scene->selection.object, axis, angle);
	else if (scene->selection.type == OBJ_CONE)
		rotate_cone((t_cone *)scene->selection.object, axis, angle);
	else if (scene->selection.type == OBJ_CAMERA)
		rotate_camera(scene, axis, angle);
}

void	resize_selection(t_scene *scene, double factor)
{
	if (scene->selection.type == OBJ_NONE || !scene->selection.object)
		return ;
	if (scene->selection.type == OBJ_SPHERE)
		resize_sphere((t_sphere *)scene->selection.object, factor);
	else if (scene->selection.type == OBJ_CYLINDER)
		resize_cylinder((t_cylinder *)scene->selection.object, factor);
	else if (scene->selection.type == OBJ_CONE)
		resize_cone((t_cone *)scene->selection.object, factor);
}
