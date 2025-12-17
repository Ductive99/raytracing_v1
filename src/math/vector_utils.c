/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <souhailelhoussain@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 18:47:24 by esouhail          #+#    #+#             */
/*   Updated: 2025/12/11 19:26:53 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "vector_math.h"
#include <math.h>
#include <stdio.h>

t_vec3	vec_new(double x, double y, double z)
{
	t_vec3	new;

	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}

t_vec3	vec_normalize(t_vec3 v)
{
	t_vec3	result;
	double	vlen;

	vlen = vec_len(v);
	if (vlen == 0 || vlen < __DBL_EPSILON__)
		return (v);
	result.x = v.x / vlen;
	result.y = v.y / vlen;
	result.z = v.z / vlen;
	return (result);
}

double	vec_len(t_vec3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

double	vec_len_squared(t_vec3 v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}

void	print_vec(t_vec3 v)
{
	printf("x: %f, y: %f, z: %f\n", v.x, v.y, v.z);
}
