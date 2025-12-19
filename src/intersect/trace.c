/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <souhailelhoussain@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 11:02:21 by esouhail          #+#    #+#             */
/*   Updated: 2025/12/19 18:00:13 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "ray.h"

static void	reset_hit(t_hit *hit)
{
	hit->hit = false;
	hit->t = DBL_MAX;
	hit->obj_type = OBJ_NONE;
	hit->object = NULL;
}

static void	get_uv_coords(t_hit *hit, double *u, double *v)
{
	if (hit->obj_type == OBJ_PLANE)
		get_plane_uv(hit->point, u, v);
	else if (hit->obj_type == OBJ_SPHERE)
		get_sphere_uv(hit->normal, u, v);
	else if (hit->obj_type == OBJ_CYLINDER)
		get_cylinder_uv((t_cylinder *)hit->object, hit->point, u, v);
	else if (hit->obj_type == OBJ_CONE)
		get_cone_uv((t_cone *)hit->object, hit->point, u, v);
}

static void	handle_selection(t_scene *scn, t_hit *hit)
{
	t_color	inv;
	double	u;
	double	v;

	if (scn->selection.type == OBJ_NONE || \
		scn->selection.object != hit->object)
		return ;
	inv.r = 255 - hit->color.r;
	inv.g = 255 - hit->color.g;
	inv.b = 255 - hit->color.b;
	get_uv_coords(hit, &u, &v);
	hit->color = get_checker_color(u, v, hit->color, inv);
}

t_color	trace_ray(t_ray ray, t_scene *scene)
{
	t_hit	closest;
	t_color	bg;

	reset_hit(&closest);
	check_spheres(ray, scene, &closest);
	check_planes(ray, scene, &closest);
	check_cylinders(ray, scene, &closest);
	check_cones(ray, scene, &closest);
	if (closest.hit)
	{
		handle_selection(scene, &closest);
		return (calculate_lighting(scene, closest.point, closest.normal,
				closest.color, ray.direction));
	}
	bg.r = 0;
	bg.g = 0;
	bg.b = 0;
	return (bg);
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
	check_cones(ray, scene, &closest);
	return (closest);
}
