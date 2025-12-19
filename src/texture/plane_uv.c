/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_uv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <esouhail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 21:13:37 by esouhail          #+#    #+#             */
/*   Updated: 2025/12/19 22:30:00 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vector_math.h"

void	get_plane_uv(t_vec3 hit_point, t_vec3 plane_normal, double *u,
		double *v)
{
	t_vec3	world_up;
	t_vec3	right;
	t_vec3	fwd;
	double	scale;

	scale = 0.05;
	world_up = (t_vec3){0, 1, 0};
	if (fabs(plane_normal.y) > 0.999)
		world_up = (t_vec3){0, 0, 1};
	right = vec_normalize(vec_cross(plane_normal, world_up));
	fwd = vec_normalize(vec_cross(right, plane_normal));
	*u = vec_dot(hit_point, right) * scale;
	*v = vec_dot(hit_point, fwd) * scale;
}
