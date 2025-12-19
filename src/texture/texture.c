/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <esouhail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 11:48:57 by esouhail          #+#    #+#             */
/*   Updated: 2025/12/19 22:31:14 by esouhail         ###   ########.fr       */
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
	u2 = (int)floor(u * scale);
	v2 = (int)floor(v * scale);
	if (((u2 + v2) & 1) == 0)
		return (c1);
	else
		return (c2);
}
