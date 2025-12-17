/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <souhailelhoussain@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 11:02:21 by esouhail          #+#    #+#             */
/*   Updated: 2025/12/17 12:58:23 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "ray.h"
#include <float.h>

static void	check_spheres(t_ray ray, t_scene *scene, t_hit *closest)
{
    t_list	*node;
    t_hit	current;

    node = scene->spheres;
    while (node)
    {
        if (hit_sphere(ray, (t_sphere *)node->obj, &current))
        {
            if (current.t > 0.001 && current.t < closest->t)
                *closest = current;
        }
        node = node->next;
    }
}

t_color	trace_ray(t_ray ray, t_scene *scene)
{
    t_hit	closest;
    t_color	background;

    closest.hit = false;
    closest.t = DBL_MAX;
    check_spheres(ray, scene, &closest);
    if (closest.hit)
        return (closest.color);
    background.r = 0;
    background.g = 0;
    background.b = 0;
    return (background);
}
