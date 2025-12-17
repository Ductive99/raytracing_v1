/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 00:00:00 by abendrih          #+#    #+#             */
/*   Updated: 2025/12/17 00:00:00 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "ray.h"
#include "vector_math.h"
#include <math.h>

/**
 * check_cylinder_height - Check if the hit point is within cylinder height
 * @ray: The ray
 * @cylinder: The cylinder
 * @t: Distance to intersection
 *
 * Return: true if within height, false otherwise
 */
static bool	check_cylinder_height(t_ray ray, t_cylinder *cylinder, double t)
{
	t_vec3	hit_point;
	t_vec3	center_to_hit;
	double	projection;

	hit_point = ray_at(ray, t);
	center_to_hit = vec_sub(hit_point, cylinder->center);
	projection = vec_dot(center_to_hit, cylinder->axis);
	return (projection >= 0 && projection <= cylinder->height);
}

/**
 * get_cylinder_equation - Calculate quadratic equation coefficients for
 * cylinder intersection
 * @ray: The ray to test
 * @cylinder: The cylinder to test against
 *
 * The cylinder equation in parametric form:
 * |P - C - ((P - C) · A) * A|² = r²
 * where P = ray.origin + t * ray.direction
 *
 * Return: Quadratic equation coefficients
 */
static t_quadratic	get_cylinder_equation(t_ray ray, t_cylinder *cylinder)
{
	t_quadratic	q;
	t_vec3		oc;
	t_vec3		d_perp;
	t_vec3		oc_perp;
	double		radius;

	oc = vec_sub(ray.origin, cylinder->center);
	radius = cylinder->diameter / 2.0;
	d_perp = vec_sub(ray.direction,
			vec_scale(vec_dot(ray.direction, cylinder->axis), cylinder->axis));
	oc_perp = vec_sub(oc, vec_scale(vec_dot(oc, cylinder->axis), cylinder->axis));
	q.a = vec_dot(d_perp, d_perp);
	q.b = 2.0 * vec_dot(d_perp, oc_perp);
	q.c = vec_dot(oc_perp, oc_perp) - radius * radius;
	q.discriminant = q.b * q.b - 4.0 * q.a * q.c;
	return (q);
}

/**
 * solve_cylinder_quadratic - Solve quadratic and find valid t for cylinder
 * @q: Quadratic equation coefficients
 * @ray: The ray
 * @cylinder: The cylinder
 *
 * Return: Valid t value or -1.0 if no valid intersection
 */
static double	solve_cylinder_quadratic(t_quadratic q, t_ray ray,
		t_cylinder *cylinder)
{
	double	t1;
	double	t2;
	double	sqrt_disc;

	if (q.discriminant < 0 || q.a < EPSILON)
		return (-1.0);
	sqrt_disc = sqrt(q.discriminant);
	t1 = (-q.b - sqrt_disc) / (2.0 * q.a);
	t2 = (-q.b + sqrt_disc) / (2.0 * q.a);
	if (t1 > EPSILON && check_cylinder_height(ray, cylinder, t1))
		return (t1);
	if (t2 > EPSILON && check_cylinder_height(ray, cylinder, t2))
		return (t2);
	return (-1.0);
}

/**
 * get_cylinder_normal - Calculate the normal at the hit point on cylinder
 * @hit_point: The point of intersection
 * @cylinder: The cylinder
 *
 * Return: Normalized normal vector
 */
static t_vec3	get_cylinder_normal(t_vec3 hit_point, t_cylinder *cylinder)
{
	t_vec3	center_to_hit;
	double	projection;
	t_vec3	axis_point;

	center_to_hit = vec_sub(hit_point, cylinder->center);
	projection = vec_dot(center_to_hit, cylinder->axis);
	axis_point = vec_add(cylinder->center,
			vec_scale(projection, cylinder->axis));
	return (vec_normalize(vec_sub(hit_point, axis_point)));
}

/**
 * hit_cylinder - Check if a ray intersects with a cylinder (tube only)
 * @ray: The ray to test
 * @cylinder: The cylinder to test against
 * @hit: Structure to fill with hit information
 *
 * Return: true if hit, false otherwise
 */
bool	hit_cylinder(t_ray ray, t_cylinder *cylinder, t_hit *hit)
{
	t_quadratic	q;
	double		t;

	q = get_cylinder_equation(ray, cylinder);
	t = solve_cylinder_quadratic(q, ray, cylinder);
	if (t < 0)
		return (false);
	hit->hit = true;
	hit->t = t;
	hit->point = ray_at(ray, t);
	hit->normal = get_cylinder_normal(hit->point, cylinder);
	hit->color = cylinder->color;
	return (true);
}
