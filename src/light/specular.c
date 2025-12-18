/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specular.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <souhailelhoussain@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 08:52:12 by esouhail          #+#    #+#             */
/*   Updated: 2025/12/18 09:01:54 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vector_math.h"

t_vec3 reflect_vec(t_vec3 L, t_vec3 N)
{
    double dot = vec_dot(N, L);
    t_vec3 scaled_normal = vec_scale(2.0 * dot, N);
    return (vec_sub(scaled_normal, L));
}

t_color get_specular(t_light *light, t_vec3 hit_point, t_vec3 normal, t_vec3 view_dir)
{
    t_vec3  light_dir;
    t_vec3  reflect_dir;
    double  spec_dot;
    double  spec_strength;
    double  shininess;
    double  specular_ratio;

    shininess = 32.0; 
    specular_ratio = 0.5;

    light_dir = vec_normalize(vec_sub(light->pos, hit_point));
    reflect_dir = reflect_vec(light_dir, normal);
    spec_dot = vec_dot(view_dir, reflect_dir);
    
    if (spec_dot <= 0)
        return ((t_color){0, 0, 0});
    spec_strength = pow(spec_dot, shininess) * specular_ratio * light->ratio;
    t_color white = {255, 255, 255};
    return (scale_color(white, spec_strength));
}
