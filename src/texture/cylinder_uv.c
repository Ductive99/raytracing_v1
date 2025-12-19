/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_uv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <souhailelhoussain@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 21:13:41 by esouhail          #+#    #+#             */
/*   Updated: 2025/12/19 21:14:35 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vector_math.h"

void	get_cylinder_uv(t_cylinder *cy, t_vec3 hit, double *u, double *v)
{
	t_vec3	dir;
	t_vec3	right;
	t_vec3	fwd;
	t_vec3	radial;
	double	h;

	dir = vec_sub(hit, cy->center);
	h = vec_dot(dir, cy->axis);
	*v = clamp_v(h / cy->height);
	radial = get_radial_vector(hit, cy->center, cy->axis);
	get_cylinder_basis(cy->axis, &right, &fwd);
	*u = get_angle_u(radial, right, fwd);
}
