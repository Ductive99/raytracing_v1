/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 00:00:00 by abendrih          #+#    #+#             */
/*   Updated: 2025/12/19 18:58:54 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vector_math.h"

void	translate_sphere(t_sphere *sp, t_vec3 delta)
{
	sp->center = vec_add(sp->center, delta);
}

void	resize_sphere(t_sphere *sp, double factor)
{
	sp->diameter *= factor;
	if (sp->diameter < 0.1)
		sp->diameter = 0.1;
}
