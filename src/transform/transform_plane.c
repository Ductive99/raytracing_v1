/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 00:00:00 by abendrih          #+#    #+#             */
/*   Updated: 2025/12/19 18:58:55 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vector_math.h"

void	translate_plane(t_plan *pl, t_vec3 delta)
{
	pl->point = vec_add(pl->point, delta);
}

void	rotate_plane(t_plan *pl, t_vec3 axis, double angle)
{
	pl->normal = rotate_vec(pl->normal, axis, angle);
}
