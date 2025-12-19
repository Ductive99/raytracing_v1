/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 11:48:57 by esouhail          #+#    #+#             */
/*   Updated: 2025/12/19 20:21:27 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vector_math.h"

t_color	get_checker_color(double u, double v, t_color c1, t_color c2)
{
	double	scale;
	int		u2;
	int		v2;

	scale = 10.0;
	u2 = floor(u * scale);
	v2 = floor(v * scale);
	if ((u2 + v2) % 2 == 0)
		return (c1);
	else
		return (c2);
}

void	get_plane_uv(t_vec3 hit_point, double *u, double *v)
void get_plane_uv(t_vec3 hit_point, t_vec3 plane_normal, double *u, double *v)
{
	*u = hit_point.x;
	*v = hit_point.z;
    t_vec3 world_up = {0, 1, 0};
    t_vec3 right;
    t_vec3 forward;
    
    if (fabs(plane_normal.y) > 0.999)
        world_up = (t_vec3){0, 0, 1};
    
    right = vec_normalize(vec_cross(plane_normal, world_up));
    forward = vec_normalize(vec_cross(right, plane_normal));
    
    *u = vec_dot(hit_point, right);
    *v = vec_dot(hit_point, forward);
}

void	get_sphere_uv(t_vec3 normal, double *u, double *v)
{
	double	phi;
	double	theta;

	phi = atan2(normal.z, normal.x);
	theta = acos(normal.y);
	*u = 1.0 - (phi + M_PI) / (2.0 * M_PI);
	*v = theta / M_PI;
}

static void	get_cylinder_basis(t_vec3 axis, t_vec3 *right, t_vec3 *forward)
{
	t_vec3 world_up = {0, 1, 0};
    
    if (fabs(axis.y) > 0.999)
        world_up = (t_vec3){0, 0, 1};

    *right = vec_normalize(vec_cross(axis, world_up));
    *forward = vec_normalize(vec_cross(*right, axis));
}

void	get_cylinder_uv(t_cylinder *cy, t_vec3 hit_point, double *u, double *v)
{
    t_vec3  vec_to_point;
    t_vec3  right;
    t_vec3  forward;
    double  hit_height;
    double  theta;
    t_vec3  point_on_axis;
    t_vec3  radial_vec;
	t_vec3	vec_to_point;
	t_vec3	right;
	t_vec3	forward;
	double	hit_height;
	double	theta;
	double	x_comp;
	double	z_comp;

    vec_to_point = vec_sub(hit_point, cy->center);
    
    hit_height = vec_dot(vec_to_point, cy->axis);
    
    *v = hit_height / cy->height;
    
    if (*v < 0.0) *v = 0.0;
    if (*v > 1.0) *v = 1.0;

    point_on_axis = vec_add(cy->center, vec_scale(hit_height, cy->axis));
    
    radial_vec = vec_sub(hit_point, point_on_axis);
    
    get_cylinder_basis(cy->axis, &right, &forward);

    double x_comp = vec_dot(radial_vec, right);
    double z_comp = vec_dot(radial_vec, forward);

    theta = atan2(z_comp, x_comp);
    *u = (theta + M_PI) / (2.0 * M_PI);
	vec_to_point = vec_sub(hit_point, cy->center);
	hit_height = vec_dot(vec_to_point, cy->axis);
	*v = (hit_height + (cy->height / 2.0)) / cy->height;
	if (*v < 0.0)
		*v = 0.0;
	if (*v > 1.0)
		*v = 1.0;
	get_cylinder_basis(cy->axis, &right, &forward);
	x_comp = vec_dot(vec_to_point, right);
	z_comp = vec_dot(vec_to_point, forward);
	theta = atan2(z_comp, x_comp);
	*u = (theta + M_PI) / (2.0 * M_PI);
}

void	get_cone_uv(t_cone *cone, t_vec3 hit_point, double *u, double *v)
{
	t_vec3	vec_to_point;
	t_vec3	right;
	t_vec3	forward;
	double	hit_height;
	double	theta;
	double	x_comp;
	double	z_comp;

	vec_to_point = vec_sub(hit_point, cone->apex);
	hit_height = vec_dot(vec_to_point, cone->axis);
	*v = hit_height / cone->height;
	if (*v < 0.0)
		*v = 0.0;
	if (*v > 1.0)
		*v = 1.0;
	get_cylinder_basis(cone->axis, &right, &forward);
	x_comp = vec_dot(vec_to_point, right);
	z_comp = vec_dot(vec_to_point, forward);
	theta = atan2(z_comp, x_comp);
	*u = (theta + M_PI) / (2.0 * M_PI);
}
