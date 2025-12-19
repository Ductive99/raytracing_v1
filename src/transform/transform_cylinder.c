/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 00:00:00 by abendrih          #+#    #+#             */
/*   Updated: 2025/12/19 18:58:55 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vector_math.h"

void	translate_cylinder(t_cylinder *cy, t_vec3 delta)
{
	cy->center = vec_add(cy->center, delta);
}

void	rotate_cylinder(t_cylinder *cy, t_vec3 axis, double angle)
{
	cy->axis = rotate_vec(cy->axis, axis, angle);
}

void	resize_cylinder(t_cylinder *cy, double factor)
{
	cy->diameter *= factor;
	cy->height *= factor;
	if (cy->diameter < 0.1)
		cy->diameter = 0.1;
	if (cy->height < 0.1)
		cy->height = 0.1;
}
