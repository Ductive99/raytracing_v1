/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_uv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <souhailelhoussain@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 18:31:40 by esouhail          #+#    #+#             */
/*   Updated: 2025/12/19 21:20:46 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vector_math.h"

void	get_cylinder_basis(t_vec3 axis, t_vec3 *right, t_vec3 *fwd)
{
	t_vec3	world_up;

	world_up = (t_vec3){0, 1, 0};
	if (fabs(axis.y) > 0.999)
		world_up = (t_vec3){0, 0, 1};
	*right = vec_normalize(vec_cross(axis, world_up));
	*fwd = vec_normalize(vec_cross(*right, axis));
}

t_vec3	get_radial_vector(t_vec3 hit, t_vec3 center, t_vec3 axis)
{
	t_vec3	dir;
	t_vec3	point_on_axis;
	double	h;

	dir = vec_sub(hit, center);
	h = vec_dot(dir, axis);
	point_on_axis = vec_add(center, vec_scale(h, axis));
	return (vec_sub(hit, point_on_axis));
}

double	get_angle_u(t_vec3 radial, t_vec3 right, t_vec3 fwd)
{
	double	theta;
	double	x_comp;
	double	y_comp;

	x_comp = vec_dot(radial, right);
	y_comp = vec_dot(radial, fwd);
	theta = atan2(y_comp, x_comp);
	return ((theta + M_PI) / (2.0 * M_PI));
}

double	clamp_v(double v)
{
	if (v < 0.0)
		return (0.0);
	if (v > 1.0)
		return (1.0);
	return (v);
}
