/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 00:00:00 by abendrih          #+#    #+#             */
/*   Updated: 2025/12/18 01:34:17 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "ray.h"
#include "vector_math.h"
#include <math.h>

t_color	apply_ambient(t_color obj_color, t_ambient *ambient)
{
	t_color	ambient_color;

	ambient_color = color_multiply(obj_color, ambient->color);
	return (color_scale(ambient_color, ambient->ratio));
}

static t_color	get_black(void)
{
	t_color	black;

	black.r = 0;
	black.g = 0;
	black.b = 0;
	return (black);
}

static t_color	compute_diffuse(t_hit *hit, t_light *light, t_scene *scene)
{
	t_vec3	light_dir;
	double	light_dist;
	double	diffuse_factor;
	t_color	diffuse;

	light_dir = vec_sub(light->pos, hit->point);
	light_dist = vec_len(light_dir);
	light_dir = vec_normalize(light_dir);
	if (is_in_shadow(hit->point, light_dir, light_dist, scene))
		return (get_black());
	diffuse_factor = vec_dot(hit->normal, light_dir);
	if (diffuse_factor < 0)
		diffuse_factor = 0;
	diffuse_factor *= light->ratio;
	diffuse = color_multiply(hit->color, light->color);
	return (color_scale(diffuse, diffuse_factor));
}

t_color	compute_lighting(t_hit *hit, t_scene *scene)
{
	t_color	final_color;
	t_color	diffuse;
	t_list	*light_node;

	final_color = apply_ambient(hit->color, &scene->ambient);
	light_node = scene->lights;
	while (light_node)
	{
		diffuse = compute_diffuse(hit, (t_light *)light_node->obj, scene);
		final_color = color_add(final_color, diffuse);
		light_node = light_node->next;
	}
	return (final_color);
}
