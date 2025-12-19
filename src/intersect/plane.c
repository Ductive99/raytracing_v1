/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 03:20:10 by abendrih          #+#    #+#             */
/*   Updated: 2025/12/19 16:19:12 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "ray.h"
#include "vector_math.h"
#include <math.h>

/**
 * hit_plane - Check if a ray intersects with a plane
 * @ray: The ray to test
 * @plane: The plane to test against
 * @hit: Structure to fill with hit information
 *
 * Formula: t = dot(plane_point - ray_origin, normal) / dot(ray_direction,
		normal)
 *
 * Return: true if hit, false otherwise
 */
bool	hit_plane(t_ray ray, t_plan *plane, t_hit *hit)
{
	double	denom;
	double	t;
	t_vec3	p0_l0;

	denom = vec_dot(ray.direction, plane->normal);
	if (fabs(denom) < EPSILON)
		return (false);
	p0_l0 = vec_sub(plane->point, ray.origin);
	t = vec_dot(p0_l0, plane->normal) / denom;
	if (t < EPSILON)
		return (false);
	hit->hit = true;
	hit->t = t;
	hit->point = ray_at(ray, t);
	if (denom > 0)
		hit->normal = vec_scale(-1.0, plane->normal);
	else
		hit->normal = plane->normal;
	hit->color = plane->color;
	return (true);
}
