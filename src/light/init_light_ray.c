/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_light_ray.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <souhailelhoussain@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 21:50:40 by esouhail          #+#    #+#             */
/*   Updated: 2025/12/19 21:51:27 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "vector_math.h"

t_ray	init_shadow_ray(t_vec3 hit_point, t_vec3 normal, t_vec3 dir)
{
	t_ray	shadow_ray;

	shadow_ray.origin = vec_add(hit_point, vec_scale(0.001, normal));
	shadow_ray.direction = dir;
	return (shadow_ray);
}
