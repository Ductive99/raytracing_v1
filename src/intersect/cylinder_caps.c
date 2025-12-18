/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_caps.c                                    :+:      :+:    :+:   */
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
#include <math.h>

static double	hit_cap(t_ray ray, t_vec3 cap_center, t_vec3 axis, double rad)
{
	double	denom;
	double	t;
	t_vec3	p;
	t_vec3	v;

	denom = vec_dot(ray.direction, axis);
	if (fabs(denom) < EPSILON)
		return (-1.0);
	t = vec_dot(vec_sub(cap_center, ray.origin), axis) / denom;
	if (t < EPSILON)
		return (-1.0);
	p = ray_at(ray, t);
	v = vec_sub(p, cap_center);
	if (vec_dot(v, v) <= rad * rad)
		return (t);
	return (-1.0);
}

static void	set_cap_hit(t_hit *hit, t_ray ray, double t, t_cylinder *cyl)
{
	hit->hit = true;
	hit->t = t;
	hit->point = ray_at(ray, t);
	hit->color = cyl->color;
}

static void	check_bottom_cap(t_ray ray, t_cylinder *cyl, t_hit *hit)
{
	double	t_bot;
	double	radius;

	radius = cyl->diameter / 2.0;
	t_bot = hit_cap(ray, cyl->center, cyl->axis, radius);
	if (t_bot > EPSILON && t_bot < hit->t)
	{
		set_cap_hit(hit, ray, t_bot, cyl);
		hit->normal = vec_scale(-1.0, cyl->axis);
		if (vec_dot(ray.direction, hit->normal) > 0)
			hit->normal = cyl->axis;
	}
}

static void	check_top_cap(t_ray ray, t_cylinder *cyl, t_hit *hit)
{
	double	t_top;
	double	radius;
	t_vec3	top_center;

	radius = cyl->diameter / 2.0;
	top_center = vec_add(cyl->center, vec_scale(cyl->height, cyl->axis));
	t_top = hit_cap(ray, top_center, cyl->axis, radius);
	if (t_top > EPSILON && t_top < hit->t)
	{
		set_cap_hit(hit, ray, t_top, cyl);
		hit->normal = cyl->axis;
		if (vec_dot(ray.direction, hit->normal) > 0)
			hit->normal = vec_scale(-1.0, cyl->axis);
	}
}

void	check_cylinder_caps(t_ray ray, t_cylinder *cyl, t_hit *hit)
{
	check_bottom_cap(ray, cyl, hit);
	check_top_cap(ray, cyl, hit);
}
