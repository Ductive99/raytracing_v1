/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 00:00:00 by abendrih          #+#    #+#             */
/*   Updated: 2025/12/17 14:53:09 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include "vector_math.h"

/**
 * ray_at - Get a point along a ray at distance t
 * @ray: The ray
 * @t: Distance along the ray
 *
 * Formula: point = origin + t * direction
 *
 * Return: The point at distance t along the ray
 */
t_vec3	ray_at(t_ray ray, double t)
{
	return (vec_add(ray.origin, vec_scale(t, ray.direction)));
}
