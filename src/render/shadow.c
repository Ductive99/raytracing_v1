/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 00:00:00 by abendrih          #+#    #+#             */
/*   Updated: 2025/12/18 01:34:18 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "ray.h"
#include "vector_math.h"

static bool	check_sphere_shadow(t_ray shadow_ray, t_scene *scene, double dist)
{
	t_list	*node;
	t_hit	hit;

	node = scene->spheres;
	while (node)
	{
		if (hit_sphere(shadow_ray, (t_sphere *)node->obj, &hit))
			if (hit.t > EPSILON && hit.t < dist)
				return (true);
		node = node->next;
	}
	return (false);
}

static bool	check_plane_shadow(t_ray shadow_ray, t_scene *scene, double dist)
{
	t_list	*node;
	t_hit	hit;

	node = scene->planes;
	while (node)
	{
		if (hit_plane(shadow_ray, (t_plan *)node->obj, &hit))
			if (hit.t > EPSILON && hit.t < dist)
				return (true);
		node = node->next;
	}
	return (false);
}

static bool	check_cylinder_shadow(t_ray shadow_ray, t_scene *scene, double dist)
{
	t_list	*node;
	t_hit	hit;

	node = scene->cylinders;
	while (node)
	{
		if (hit_cylinder(shadow_ray, (t_cylinder *)node->obj, &hit))
			if (hit.t > EPSILON && hit.t < dist)
				return (true);
		node = node->next;
	}
	return (false);
}

bool	is_in_shadow(t_vec3 point, t_vec3 light_dir, double light_dist,
		t_scene *scene)
{
	t_ray	shadow_ray;

	shadow_ray.origin = vec_add(point, vec_scale(EPSILON, light_dir));
	shadow_ray.direction = light_dir;
	if (check_sphere_shadow(shadow_ray, scene, light_dist))
		return (true);
	if (check_plane_shadow(shadow_ray, scene, light_dist))
		return (true);
	if (check_cylinder_shadow(shadow_ray, scene, light_dist))
		return (true);
	return (false);
}
