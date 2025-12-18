/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <souhailelhoussain@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 22:40:54 by esouhail          #+#    #+#             */
/*   Updated: 2025/12/18 09:02:53 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vector_math.h"

t_vec3 vec_negate(t_vec3 v)
{
    return ((t_vec3){-v.x, -v.y, -v.z});
}

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

t_color calculate_lighting(t_scene *scene, t_vec3 hit_point, t_vec3 normal, t_color obj_color, t_vec3 ray_dir)
{
    t_color total_diffuse;
    t_color total_specular;
    t_color ambient_component;
    t_color light_contribution;
    t_color spec_contribution;
    t_list  *current_light_node;
    t_light *current_light;
    t_vec3  view_dir;

    total_diffuse = (t_color){0, 0, 0};
    total_specular = (t_color){0, 0, 0};
    view_dir = vec_normalize(vec_negate(ray_dir));

    current_light_node = scene->lights;
    while (current_light_node)
    {
        current_light = (t_light *)current_light_node->obj;

        if (!is_in_shadow(scene, current_light, hit_point, normal))
        {
            light_contribution = get_light_contribution(current_light, hit_point, normal);
            total_diffuse = add_colors(total_diffuse, light_contribution);
            
            spec_contribution = get_specular(current_light, hit_point, normal, view_dir);
            total_specular = add_colors(total_specular, spec_contribution);
        }
        current_light_node = current_light_node->next;
    }

    ambient_component = scale_color(scene->ambient.color, scene->ambient.ratio);
    
    t_color ambient_obj;
    ambient_obj.r = (int)(obj_color.r * ambient_component.r / 255.0);
    ambient_obj.g = (int)(obj_color.g * ambient_component.g / 255.0);
    ambient_obj.b = (int)(obj_color.b * ambient_component.b / 255.0);
    
    t_color diffuse_obj;
    diffuse_obj.r = (int)(obj_color.r * total_diffuse.r / 255.0);
    diffuse_obj.g = (int)(obj_color.g * total_diffuse.g / 255.0);
    diffuse_obj.b = (int)(obj_color.b * total_diffuse.b / 255.0);
    
    t_color final_color;
    final_color.r = clamp(ambient_obj.r + diffuse_obj.r + total_specular.r);
    final_color.g = clamp(ambient_obj.g + diffuse_obj.g + total_specular.g);
    final_color.b = clamp(ambient_obj.b + diffuse_obj.b + total_specular.b);

    return (final_color);
}
