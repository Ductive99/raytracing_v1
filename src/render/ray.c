/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <souhailelhoussain@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 15:35:33 by esouhail          #+#    #+#             */
/*   Updated: 2025/12/14 15:37:02 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray.h"
#include "vector_math.h"

t_vec3	ray_at(t_ray ray, double t)
{
	return (vec_add(ray.origin, vec_scale(t, ray.direction)));
}
