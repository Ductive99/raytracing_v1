/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_cone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 00:00:00 by abendrih          #+#    #+#             */
/*   Updated: 2025/12/19 18:58:55 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vector_math.h"

void	translate_cone(t_cone *co, t_vec3 delta)
{
	co->apex = vec_add(co->apex, delta);
}

void	rotate_cone(t_cone *co, t_vec3 axis, double angle)
{
	co->axis = rotate_vec(co->axis, axis, angle);
}

void	resize_cone(t_cone *co, double factor)
{
	co->height *= factor;
	if (co->height < 0.1)
		co->height = 0.1;
}
