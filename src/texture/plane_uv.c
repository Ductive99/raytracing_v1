/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_uv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <souhailelhoussain@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 21:13:37 by esouhail          #+#    #+#             */
/*   Updated: 2025/12/19 21:18:38 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vector_math.h"

void get_plane_uv(t_vec3 hit_point, t_vec3 plane_normal, double *u, double *v)
{
    t_vec3 world_up = {0, 1, 0};
    t_vec3 right;
    t_vec3 forward;
    
    if (fabs(plane_normal.y) > 0.999)
        world_up = (t_vec3){0, 0, 1};
    
    right = vec_normalize(vec_cross(plane_normal, world_up));
    forward = vec_normalize(vec_cross(right, plane_normal));
    
    *u = vec_dot(hit_point, right);
    *v = vec_dot(hit_point, forward);
}

