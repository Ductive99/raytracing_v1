/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 03:20:26 by esouhail          #+#    #+#             */
/*   Updated: 2025/12/19 21:39:17 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "ray.h"
#include "vector_math.h"

int	is_in_shadow(t_scene *scene, t_light *light, t_vec3 hit_point,
		t_vec3 normal)
{
	t_ray	shadow_ray;
	t_vec3	light_dir;
	double	dist_to_light;
	t_hit	shadow_hit;
	t_list	*node;

	light_dir = vec_sub(light->pos, hit_point);
	dist_to_light = vec_len(light_dir);
	light_dir = vec_normalize(light_dir);
	// Offset to aviod acne dots
	shadow_ray.origin = vec_add(hit_point, vec_scale(0.001, normal));
	shadow_ray.direction = light_dir;
	shadow_hit.t = dist_to_light;
	// Check spheres
	node = scene->spheres;
	while (node)
	{
		if (hit_sphere(shadow_ray, (t_sphere *)node->obj, &shadow_hit))
			if (shadow_hit.t < dist_to_light)
				return (1);
		node = node->next;
	}
	// Check planes
	node = scene->planes;
	while (node)
	{
		if (hit_plane(shadow_ray, (t_plan *)node->obj, &shadow_hit))
			if (shadow_hit.t < dist_to_light)
				return (1);
		node = node->next;
	}
	// Check cylinders
	node = scene->cylinders;
	while (node)
	{
		if (hit_cylinder(shadow_ray, (t_cylinder *)node->obj, &shadow_hit))
			if (shadow_hit.t < dist_to_light)
				return (1);
		if (hit_cylinder_caps(shadow_ray, (t_cylinder *)node->obj, &shadow_hit))
			if (shadow_hit.t < dist_to_light)
				return (1);
		node = node->next;
	}
	// Check cones
	node = scene->cones;
	while (node)
	{
		if (hit_cone(shadow_ray, (t_cone *)node->obj, &shadow_hit))
			if (shadow_hit.t < dist_to_light)
				return (1);
		node = node->next;
	}
	return (0);
}
