/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 21:00:34 by abendrih          #+#    #+#             */
/*   Updated: 2025/12/19 16:18:01 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "ray.h"
#include "vector_math.h"
#include <math.h>

/**
 * check_cone_height - Check if the hit point is within cone height
 * @ray: The ray
 * @cone: The cone
 * @t: Distance to intersection
 *
 * Return: true if within height, false otherwise
 */
static bool	check_cone_height(t_ray ray, t_cone *cone, double t)
{
	t_vec3	hit_point;
	t_vec3	apex_to_hit;
	double	projection;

	hit_point = ray_at(ray, t);
	apex_to_hit = vec_sub(hit_point, cone->apex);
	projection = vec_dot(apex_to_hit, cone->axis);
	return (projection >= 0 && projection <= cone->height);
}

/**
 * get_cone_equation - Calculate quadratic equation coefficients for
 * cone intersection
 * @ray: The ray to test
 * @cone: The cone to test against
 *
 * The cone equation: |P - A - ((P - A) · V) * V|² = (tan(θ) * ((P - A) · V))²
 * where P = ray.origin + t * ray.direction, A = apex, V = axis
 *
 * Return: Quadratic equation coefficients
 */
static t_quadratic	get_cone_equation(t_ray ray, t_cone *cone)
{
	t_quadratic	q;
	t_vec3		oc;
	double		cos2;
	double		sin2;
	double		dv;
	double		ocv;

	oc = vec_sub(ray.origin, cone->apex);
	cos2 = cos(cone->angle * M_PI / 180.0);
	cos2 = cos2 * cos2;
	sin2 = 1.0 - cos2;
	dv = vec_dot(ray.direction, cone->axis);
	ocv = vec_dot(oc, cone->axis);
	q.a = vec_dot(ray.direction, ray.direction) * cos2 - dv * dv;
	q.b = 2.0 * (vec_dot(ray.direction, oc) * cos2 - dv * ocv);
	q.c = vec_dot(oc, oc) * cos2 - ocv * ocv;
	q.discriminant = q.b * q.b - 4.0 * q.a * q.c;
	return (q);
}

/**
 * solve_cone_quadratic - Solve quadratic and find valid t for cone
 * @q: Quadratic equation coefficients
 * @ray: The ray
 * @cone: The cone
 *
 * Return: Valid t value or -1.0 if no valid intersection
 */
static double	solve_cone_quadratic(t_quadratic q, t_ray ray, t_cone *cone)
{
	double	t1;
	double	t2;
	double	sqrt_disc;

	if (q.discriminant < 0 || fabs(q.a) < EPSILON)
		return (-1.0);
	sqrt_disc = sqrt(q.discriminant);
	t1 = (-q.b - sqrt_disc) / (2.0 * q.a);
	t2 = (-q.b + sqrt_disc) / (2.0 * q.a);
	if (t1 > EPSILON && check_cone_height(ray, cone, t1))
		return (t1);
	if (t2 > EPSILON && check_cone_height(ray, cone, t2))
		return (t2);
	return (-1.0);
}

/**
 * get_cone_normal - Calculate the normal at the hit point on cone
 * @hit_point: The point of intersection
 * @cone: The cone
 *
 * Return: Normalized normal vector
 */
static t_vec3	get_cone_normal(t_vec3 hit_point, t_cone *cone)
{
	t_vec3	apex_to_hit;
	double	projection;
	t_vec3	axis_point;
	t_vec3	radial;
	double	tan_angle;

	apex_to_hit = vec_sub(hit_point, cone->apex);
	projection = vec_dot(apex_to_hit, cone->axis);
	axis_point = vec_add(cone->apex, vec_scale(projection, cone->axis));
	radial = vec_sub(hit_point, axis_point);
	tan_angle = tan(cone->angle * M_PI / 180.0);
	return (vec_normalize(vec_sub(radial, vec_scale(tan_angle * vec_len(radial),
					cone->axis))));
}

/**
 * hit_cone - Check if a ray intersects with a cone (surface only)
 * @ray: The ray to test
 * @cone: The cone to test against
 * @hit: Structure to fill with hit information
 *
 * Return: true if hit, false otherwise
 */
bool	hit_cone(t_ray ray, t_cone *cone, t_hit *hit)
{
	t_quadratic	q;
	double		t;

	q = get_cone_equation(ray, cone);
	t = solve_cone_quadratic(q, ray, cone);
	if (t < 0)
		return (false);
	hit->hit = true;
	hit->t = t;
	hit->point = ray_at(ray, t);
	hit->normal = get_cone_normal(hit->point, cone);
	hit->color = cone->color;
	return (true);
}

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
	t_vec3	base_center;
	double	denom;
	double	t;
	t_vec3	hit_point;
	double	dist;
	double	radius;

	base_center = vec_add(cone->apex, vec_scale(cone->height, cone->axis));
	denom = vec_dot(ray.direction, cone->axis);
	if (fabs(denom) < EPSILON)
		return (false);
	t = vec_dot(vec_sub(base_center, ray.origin), cone->axis) / denom;
	if (t < EPSILON)
		return (false);
	hit_point = ray_at(ray, t);
	dist = vec_len(vec_sub(hit_point, base_center));
	radius = cone->height * tan(cone->angle * M_PI / 180.0);
	if (dist > radius)
		return (false);
	hit->hit = true;
	hit->t = t;
	hit->point = hit_point;
	hit->normal = cone->axis;
	if (denom > 0)
		hit->normal = vec_scale(-1, hit->normal);
	hit->color = cone->color;
	return (true);
}
