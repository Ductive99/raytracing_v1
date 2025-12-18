/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <souhailelhoussain@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 22:47:22 by esouhail          #+#    #+#             */
/*   Updated: 2025/12/17 22:52:13 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	clamp(int value)
{
	if (value > 255)
		return (255);
	if (value < 0)
		return (0);
	return (value);
}

t_color	add_colors(t_color c1, t_color c2)
{
	return ((t_color){
		clamp(c1.r + c2.r),
		clamp(c1.g + c2.g),
		clamp(c1.b + c2.b)
	});
}

t_color	scale_color(t_color c, double intensity)
{
	return ((t_color){
		clamp((int)(c.r * intensity)),
		clamp((int)(c.g * intensity)),
		clamp((int)(c.b * intensity))
	});
}
