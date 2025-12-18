/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <souhailelhoussain@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 11:02:21 by esouhail          #+#    #+#             */
/*   Updated: 2025/12/18 21:10:41 by esouhail         ###   ########.fr       */
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
			{
				*closest = current;
				closest->obj_type = OBJ_SPHERE;
				closest->object = node->obj;
			}
		}
		node = node->next;
	}
}

static void	check_planes(t_ray ray, t_scene *scene, t_hit *closest)
{
	t_list	*node;
	t_hit	current;

	node = scene->planes;
	while (node)
	{
		if (hit_plane(ray, (t_plan *)node->obj, &current))
		{
			if (current.t > 0.001 && current.t < closest->t)
			{
				*closest = current;
				closest->obj_type = OBJ_PLANE;
				closest->object = node->obj;
			}
		}
		node = node->next;
	}
}

static void	check_cylinders(t_ray ray, t_scene *scene, t_hit *closest)
{
	t_list	*node;
	t_hit	current;

	node = scene->cylinders;
	while (node)
	{
		if (hit_cylinder(ray, (t_cylinder *)node->obj, &current))
		{
			if (current.t > 0.001 && current.t < closest->t)
			{
				*closest = current;
				closest->obj_type = OBJ_CYLINDER;
				closest->object = node->obj;
			}
		}
		if (hit_cylinder_caps(ray, (t_cylinder *)node->obj, &current))
		{
			if (current.t > 0.001 && current.t < closest->t)
			{
				*closest = current;
				closest->obj_type = OBJ_CYLINDER;
				closest->object = node->obj;
			}
		}
		node = node->next;
	}
}

t_color	trace_ray(t_ray ray, t_scene *scene)
{
    t_hit	closest;
    t_color	background;
    double	u;
    double	v;

    closest.hit = false;
    closest.t = DBL_MAX;
    closest.obj_type = OBJ_NONE;
    closest.object = NULL;
    check_spheres(ray, scene, &closest);
    check_planes(ray, scene, &closest);
    check_cylinders(ray, scene, &closest);
    if (closest.hit)
    {
        // Apply checkerboard pattern only if this object is selected
        if (scene->selection.type != OBJ_NONE && 
            scene->selection.object == closest.object)
        {
            t_color inverted;
            inverted.r = 255 - closest.color.r;
            inverted.g = 255 - closest.color.g;
            inverted.b = 255 - closest.color.b;
            
            if (closest.obj_type == OBJ_PLANE)
            {
                get_plane_uv(closest.point, &u, &v);
                closest.color = get_checker_color(u, v, closest.color, inverted);
            }
            else if (closest.obj_type == OBJ_SPHERE)
            {
                get_sphere_uv(closest.normal, &u, &v);
                closest.color = get_checker_color(u, v, closest.color, inverted);
            }
            else if (closest.obj_type == OBJ_CYLINDER)
            {
                get_cylinder_uv((t_cylinder *)closest.object, closest.point, &u, &v);
                closest.color = get_checker_color(u, v, closest.color, inverted);
            }
        }
        
        return (calculate_lighting(scene, closest.point, closest.normal,
                closest.color, ray.direction));
    }
    background.r = 0;
    background.g = 0;
    background.b = 0;
    return (background);
}

t_hit	trace_ray_select(t_ray ray, t_scene *scene)
{
	t_hit	closest;

	closest.hit = false;
	closest.t = DBL_MAX;
	closest.obj_type = OBJ_NONE;
	closest.object = NULL;
	check_spheres(ray, scene, &closest);
	check_planes(ray, scene, &closest);
	check_cylinders(ray, scene, &closest);
	return (closest);
}
