/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_uv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <souhailelhoussain@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 21:13:29 by esouhail          #+#    #+#             */
/*   Updated: 2025/12/19 21:14:02 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vector_math.h"

void	get_sphere_uv(t_vec3 normal, double *u, double *v)
{
	double	phi;
	double	theta;

	phi = atan2(normal.z, normal.x);
	theta = acos(normal.y);
	*u = 1.0 - (phi + M_PI) / (2.0 * M_PI);
	*v = theta / M_PI;
}
