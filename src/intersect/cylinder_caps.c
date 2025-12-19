/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_caps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <souhailelhoussain@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 02:29:10 by abendrih          #+#    #+#             */
/*   Updated: 2025/12/19 18:06:32 by esouhail         ###   ########.fr       */
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

static void	set_cap_hit(t_hit *hit, t_ray r, double t, t_vec3 normal)
{
	hit->hit = true;
	hit->t = t;
	hit->point = ray_at(r, t);
	hit->normal = normal;
	if (vec_dot(r.direction, hit->normal) > 0)
		hit->normal = vec_scale(-1.0, hit->normal);
}

bool	hit_cylinder_caps(t_ray ray, t_cylinder *cyl, t_hit *hit)
{
	double	t_bot;
	double	t_top;
	double	rad;
	t_vec3	top;

	rad = cyl->diameter / 2.0;
	top = vec_add(cyl->center, vec_scale(cyl->height, cyl->axis));
	t_bot = hit_disk(ray, cyl->center, cyl->axis, rad);
	t_top = hit_disk(ray, top, cyl->axis, rad);
	hit->hit = false;
	if (t_bot > EPSILON && (t_bot < t_top || t_top < EPSILON))
		set_cap_hit(hit, ray, t_bot, vec_scale(-1.0, cyl->axis));
	else if (t_top > EPSILON)
		set_cap_hit(hit, ray, t_top, cyl->axis);
	if (hit->hit)
		hit->color = cyl->color;
	return (hit->hit);
}
