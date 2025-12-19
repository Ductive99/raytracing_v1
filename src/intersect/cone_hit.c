/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_hit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <souhailelhoussain@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 18:11:44 by esouhail          #+#    #+#             */
/*   Updated: 2025/12/19 18:15:17 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "ray.h"
#include "vector_math.h"
#include <math.h>

/**
 * hit_cone_cap - Check if a ray intersects with the cone base cap
 * @ray: The ray to test
 * @cone: The cone to test against
 * @hit: Structure to fill with hit information
 *
 * Return: true if hit, false otherwise
 */
bool	hit_cone_cap(t_ray ray, t_cone *cone, t_hit *hit)
{
	t_vec3	base;
	t_vec3	p;
	double	denom;
	double	t;
	double	rad;

	denom = vec_dot(ray.direction, cone->axis);
	if (fabs(denom) < EPSILON)
		return (false);
	base = vec_add(cone->apex, vec_scale(cone->height, cone->axis));
	t = vec_dot(vec_sub(base, ray.origin), cone->axis) / denom;
	if (t < EPSILON)
		return (false);
	p = ray_at(ray, t);
	rad = cone->height * tan(cone->angle * M_PI / 180.0);
	if (vec_len(vec_sub(p, base)) > rad)
		return (false);
	hit->hit = true;
	hit->t = t;
	hit->point = p;
	hit->normal = cone->axis;
	if (denom > 0)
		hit->normal = vec_scale(-1, hit->normal);
	hit->color = cone->color;
	return (true);
}
