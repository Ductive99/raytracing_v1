/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_caps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 02:29:10 by abendrih          #+#    #+#             */
/*   Updated: 2025/12/18 02:29:27 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "ray.h"
#include "vector_math.h"
#include <math.h>

static double	hit_disk(t_ray ray, t_vec3 center, t_vec3 normal, double radius)
{
	double	denom;
	double	t;
	t_vec3	hit_point;
	t_vec3	v;

	denom = vec_dot(ray.direction, normal);
	if (fabs(denom) < EPSILON)
		return (-1.0);
	t = vec_dot(vec_sub(center, ray.origin), normal) / denom;
	if (t < EPSILON)
		return (-1.0);
	hit_point = ray_at(ray, t);
	v = vec_sub(hit_point, center);
	if (vec_dot(v, v) <= radius * radius)
		return (t);
	return (-1.0);
}

bool	hit_cylinder_caps(t_ray ray, t_cylinder *cyl, t_hit *hit)
{
	double	t_bot;
	double	t_top;
	double	radius;
	t_vec3	top_center;

	radius = cyl->diameter / 2.0;
	top_center = vec_add(cyl->center, vec_scale(cyl->height, cyl->axis));
	t_bot = hit_disk(ray, cyl->center, cyl->axis, radius);
	t_top = hit_disk(ray, top_center, cyl->axis, radius);
	hit->hit = false;
	if (t_bot > EPSILON && (t_bot < t_top || t_top < EPSILON))
	{
		hit->hit = true;
		hit->t = t_bot;
		hit->point = ray_at(ray, t_bot);
		hit->normal = vec_scale(-1.0, cyl->axis);
		if (vec_dot(ray.direction, hit->normal) > 0)
			hit->normal = cyl->axis;
		hit->color = cyl->color;
	}
	else if (t_top > EPSILON)
	{
		hit->hit = true;
		hit->t = t_top;
		hit->point = ray_at(ray, t_top);
		hit->normal = cyl->axis;
		if (vec_dot(ray.direction, hit->normal) > 0)
			hit->normal = vec_scale(-1.0, cyl->axis);
		hit->color = cyl->color;
	}
	return (hit->hit);
}
