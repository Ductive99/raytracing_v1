/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specular.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <souhailelhoussain@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 08:52:12 by esouhail          #+#    #+#             */
/*   Updated: 2025/12/19 21:36:59 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vector_math.h"

t_vec3	reflect_vec(t_vec3 L, t_vec3 N)
{
	t_vec3	scaled_normal;
	double	dot;

	dot = vec_dot(N, L);
	scaled_normal = vec_scale(2.0 * dot, N);
	return (vec_sub(scaled_normal, L));
}

t_color	get_specular(t_light *light, t_vec3 hit_point,
	t_vec3 normal, t_vec3 view_dir)
{
	t_vec3	light_dir;
	t_vec3	reflect_dir;
	double	dot;
	double	strength;

	light_dir = vec_normalize(vec_sub(light->pos, hit_point));
	reflect_dir = reflect_vec(light_dir, normal);
	dot = vec_dot(view_dir, reflect_dir);
	if (dot <= 0)
		return ((t_color){0, 0, 0});
	strength = pow(dot, 32.0) * 0.5 * light->ratio;
	return (scale_color((t_color){255, 255, 255}, strength));
}
