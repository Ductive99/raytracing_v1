/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 00:00:00 by abendrih          #+#    #+#             */
/*   Updated: 2025/12/18 01:34:17 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	clamp_color(int value)
{
	if (value < 0)
		return (0);
	if (value > 255)
		return (255);
	return (value);
}

t_color	color_scale(t_color c, double factor)
{
	t_color	result;

	result.r = clamp_color((int)(c.r * factor));
	result.g = clamp_color((int)(c.g * factor));
	result.b = clamp_color((int)(c.b * factor));
	return (result);
}

t_color	color_add(t_color c1, t_color c2)
{
	t_color	result;

	result.r = clamp_color(c1.r + c2.r);
	result.g = clamp_color(c1.g + c2.g);
	result.b = clamp_color(c1.b + c2.b);
	return (result);
}

t_color	color_multiply(t_color c1, t_color c2)
{
	t_color	result;

	result.r = clamp_color((c1.r * c2.r) / 255);
	result.g = clamp_color((c1.g * c2.g) / 255);
	result.b = clamp_color((c1.b * c2.b) / 255);
	return (result);
}
