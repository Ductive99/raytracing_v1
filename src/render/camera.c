/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 11:41:35 by esouhail          #+#    #+#             */
/*   Updated: 2025/12/19 21:51:29 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #ifndef M_PI
// # define M_PI 3.14159265358979323846
// #endif

#include "minirt.h"
#include "vector_math.h"
#include <math.h>

static t_vec3	get_camera_right(t_vec3 forward)
{
	t_vec3	world_up;
	t_vec3	right;

	world_up = (t_vec3){0, 1, 0};
	if (fabs(forward.y) > 0.999)
		world_up = (t_vec3){0, 0, 1};
	right = vec_cross(forward, world_up);
	return (vec_normalize(right));
}

static t_vec3	get_camera_up(t_vec3 forward, t_vec3 right)
{
	return (vec_normalize(vec_cross(right, forward)));
}

static void	setup_camera_vectors(t_cam *cam, double vp_w, double vp_h)
{
	t_vec3	cam_right;
	t_vec3	cam_up;

	cam_right = get_camera_right(cam->dir);
	cam_up = get_camera_up(cam->dir, cam_right);
	cam->viewport_u = vec_scale(vp_w, cam_right);
	cam->viewport_v = vec_scale(-vp_h, cam_up);
}

void	setup_camera(t_cam *cam, int width, int height)
{
	double	aspect_ratio;
	double	vp_h;
	double	vp_w;

	aspect_ratio = (double)width / (double)height;
	vp_h = 2.0 * tan((cam->fov * M_PI / 180.0) / 2.0);
	vp_w = vp_h * aspect_ratio;
	setup_camera_vectors(cam, vp_w, vp_h);
	cam->viewport_upper_left = vec_add(cam->position, vec_sub(cam->dir,
				vec_add(vec_scale(0.5, cam->viewport_u), vec_scale(0.5,
						cam->viewport_v))));
	cam->pixel_delta_u = vec_scale(1.0 / width, cam->viewport_u);
	cam->pixel_delta_v = vec_scale(1.0 / height, cam->viewport_v);
}

t_ray	get_camera_ray(t_cam *cam, int x, int y)
{
	t_ray	ray;
	t_vec3	pixel_center;

	pixel_center = vec_add(cam->viewport_upper_left, vec_add(vec_scale(x + 0.5,
					cam->pixel_delta_u), vec_scale(y + 0.5,
					cam->pixel_delta_v)));
	ray.origin = cam->position;
	ray.direction = vec_normalize(vec_sub(pixel_center, cam->position));
	return (ray);
}
