/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <souhailelhoussain@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 22:40:54 by esouhail          #+#    #+#             */
/*   Updated: 2025/12/18 07:11:51 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vector_math.h"

t_color get_light_contribution(t_light *light, t_vec3 hit_point, t_vec3 normal)
{
    t_vec3  light_dir;
    t_color diffuse_color;
    double  diffuse_strength;

    light_dir = vec_normalize(vec_sub(light->pos, hit_point));
    diffuse_strength = fmax(0.0, vec_dot(normal, light_dir));
    diffuse_strength *= light->ratio;
    diffuse_color = scale_color(light->color, diffuse_strength);    
    return (diffuse_color);
}

t_color calculate_lighting(t_scene *scene, t_vec3 hit_point, t_vec3 normal, t_color obj_color)
{
    t_color total_diffuse;
    t_color ambient_component;
    t_color light_contribution;
    t_list  *current_light_node;
    t_light *current_light;

    total_diffuse = (t_color){0, 0, 0};

    current_light_node = scene->lights;
    while (current_light_node)
    {
        current_light = (t_light *)current_light_node->obj;

		if (!is_in_shadow(scene, current_light, hit_point, normal))
        {
        	light_contribution = get_light_contribution(current_light, hit_point, normal);
        	total_diffuse = add_colors(total_diffuse, light_contribution);
		}
        current_light_node = current_light_node->next;
    }

    ambient_component = scale_color(scene->ambient.color, scene->ambient.ratio);
    t_color total_light_energy = add_colors(ambient_component, total_diffuse);
    t_color final_color;
    final_color.r = clamp((int)(obj_color.r * total_light_energy.r / 255.0));
    final_color.g = clamp((int)(obj_color.g * total_light_energy.g / 255.0));
    final_color.b = clamp((int)(obj_color.b * total_light_energy.b / 255.0));

    return (final_color);
}
