/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <souhailelhoussain@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 12:02:22 by esouhail          #+#    #+#             */
/*   Updated: 2025/12/14 15:50:34 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "ray.h"
#include "vector_math.h"
#include <math.h>

static double	solve_quadratic(t_quadratic q)
{
	double	t1;
	double	t2;

	if (q.discriminant < 0)
		return (-1.0);
	t1 = (-q.b - sqrt(q.discriminant)) / (2.0 * q.a);
	t2 = (-q.b + sqrt(q.discriminant)) / (2.0 * q.a);
	if (t1 > EPSILON)
		return (t1);
	else if (t2 > EPSILON)
		return (t2);
	return (-1.0);
}

// q.a = vec_dot(ray.direction, ray.direction);
//     = 1.0 since direction must be normalized
static t_quadratic	get_sphere_equation(t_ray ray, t_sphere *sphere)
{
	t_quadratic	q;
	t_vec3		oc;
	double		radius;

	oc = vec_sub(ray.origin, sphere->center);
	radius = sphere->diameter / 2.0;
	q.a = 1.0;
	q.b = 2.0 * vec_dot(oc, ray.direction);
	q.c = vec_dot(oc, oc) - radius * radius;
	q.discriminant = q.b * q.b - 4 * q.a * q.c;
	return (q);
}

bool	hit_sphere(t_ray ray, t_sphere *sphere, t_hit *hit)
{
	t_quadratic	q;
	double		t;

	q = get_sphere_equation(ray, sphere);
	t = solve_quadratic(q);
	if (t < 0)
		return (false);
	hit->hit = true;
	hit->t = t;
	hit->point = ray_at(ray, hit->t);
	hit->normal = vec_normalize(vec_sub(hit->point, sphere->center));
	hit->color = sphere->color;
	return (true);
}
