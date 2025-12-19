/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <souhailelhoussain@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 22:40:54 by esouhail          #+#    #+#             */
/*   Updated: 2025/12/19 20:31:57 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vector_math.h"

t_vec3	vec_negate(t_vec3 v)
{
	return ((t_vec3){-v.x, -v.y, -v.z});
}

t_color	get_light_contribution(t_light *light, t_vec3 hit_point, t_vec3 normal)
{
	t_vec3	light_dir;
	t_color	diffuse_color;
	double	diffuse_strength;

	light_dir = vec_normalize(vec_sub(light->pos, hit_point));
	diffuse_strength = fmax(0.0, vec_dot(normal, light_dir));
	diffuse_strength *= light->ratio;
	diffuse_color = scale_color(light->color, diffuse_strength);
	return (diffuse_color);
}

static t_color	mix_final_color(t_color obj, t_color light, t_color spec)
{
	t_color	fin;

	fin.r = clamp((int)(obj.r * light.r / 255.0) + spec.r);
	fin.g = clamp((int)(obj.g * light.g / 255.0) + spec.g);
	fin.b = clamp((int)(obj.b * light.b / 255.0) + spec.b);
	return (fin);
}

static t_color	sum_lights(t_scene *scn, t_hit hit, t_vec3 view, t_color *spec)
{
	t_list	*node;
	t_color	diff;
	t_light	*l;

	diff = (t_color){0, 0, 0};
	*spec = (t_color){0, 0, 0};
	node = scn->lights;
	while (node)
	{
		l = (t_light *)node->obj;
		if (!is_in_shadow(scn, l, hit.point, hit.normal))
		{
			diff = add_colors(diff, \
				get_light_contribution(l, hit.point, hit.normal));
			*spec = add_colors(*spec, \
				get_specular(l, hit.point, hit.normal, view));
		}
		node = node->next;
	}
	return (diff);
}

t_color	calculate_lighting(t_scene *scene, t_hit hit, t_vec3 ray_dir)
{
	t_color	spec;
	t_color	diff;
	t_color	amb;
	t_vec3	view;

	view = vec_normalize(vec_negate(ray_dir));
	diff = sum_lights(scene, hit, view, &spec);
	amb = scale_color(scene->ambient.color, scene->ambient.ratio);
	return (mix_final_color(hit.color, add_colors(amb, diff), spec));
}
