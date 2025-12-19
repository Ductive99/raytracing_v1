/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <souhailelhoussain@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 03:20:26 by esouhail          #+#    #+#             */
/*   Updated: 2025/12/19 21:50:26 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "ray.h"
#include "vector_math.h"

static int	check_sphere_shadow(t_list *spheres, t_ray ray, double dist)
{
	t_hit	shadow_hit;

	shadow_hit.t = dist;
	while (spheres)
	{
		if (hit_sphere(ray, (t_sphere *)spheres->obj, &shadow_hit))
			if (shadow_hit.t < dist)
				return (1);
		spheres = spheres->next;
	}
	return (0);
}

static int	check_plane_shadow(t_list *planes, t_ray ray, double dist)
{
	t_hit	shadow_hit;

	shadow_hit.t = dist;
	while (planes)
	{
		if (hit_plane(ray, (t_plan *)planes->obj, &shadow_hit))
			if (shadow_hit.t < dist)
				return (1);
		planes = planes->next;
	}
	return (0);
}

static int	check_cylinder_shadow(t_list *cyls, t_ray ray, double dist)
{
	t_hit	shadow_hit;

	shadow_hit.t = dist;
	while (cyls)
	{
		if (hit_cylinder(ray, (t_cylinder *)cyls->obj, &shadow_hit))
			if (shadow_hit.t < dist)
				return (1);
		if (hit_cylinder_caps(ray, (t_cylinder *)cyls->obj, &shadow_hit))
			if (shadow_hit.t < dist)
				return (1);
		cyls = cyls->next;
	}
	return (0);
}

static int	check_cone_shadow(t_list *cones, t_ray ray, double dist)
{
	t_hit	shadow_hit;

	shadow_hit.t = dist;
	while (cones)
	{
		if (hit_cone(ray, (t_cone *)cones->obj, &shadow_hit))
			if (shadow_hit.t < dist)
				return (1);
		cones = cones->next;
	}
	return (0);
}

int	is_in_shadow(t_scene *scene, t_light *light, t_vec3 hit, t_vec3 norm)
{
	t_ray	shadow_ray;
	t_vec3	light_dir;
	double	dist;

	light_dir = vec_sub(light->pos, hit);
	dist = vec_len(light_dir);
	light_dir = vec_normalize(light_dir);
	shadow_ray = init_shadow_ray(hit, norm, light_dir);
	if (check_sphere_shadow(scene->spheres, shadow_ray, dist))
		return (1);
	if (check_plane_shadow(scene->planes, shadow_ray, dist))
		return (1);
	if (check_cylinder_shadow(scene->cylinders, shadow_ray, dist))
		return (1);
	if (check_cone_shadow(scene->cones, shadow_ray, dist))
		return (1);
	return (0);
}
