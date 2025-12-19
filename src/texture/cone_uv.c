/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_uv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <souhailelhoussain@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 21:13:33 by esouhail          #+#    #+#             */
/*   Updated: 2025/12/19 21:14:52 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vector_math.h"

void	get_cone_uv(t_cone *cone, t_vec3 hit, double *u, double *v)
{
	t_vec3	dir;
	t_vec3	right;
	t_vec3	fwd;
	t_vec3	radial;
	double	h;

	dir = vec_sub(hit, cone->apex);
	h = vec_dot(dir, cone->axis);
	*v = clamp_v(h / cone->height);
	radial = get_radial_vector(hit, cone->apex, cone->axis);
	get_cylinder_basis(cone->axis, &right, &fwd);
	*u = get_angle_u(radial, right, fwd);
}
