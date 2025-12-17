/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <souhailelhoussain@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 11:41:35 by esouhail          #+#    #+#             */
/*   Updated: 2025/12/17 16:33:52 by esouhail         ###   ########.fr       */
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

void	setup_camera(t_cam *cam, int width, int height)
{
	double	aspect_ratio;
	double	viewport_height;
	double	viewport_width;
	double	focal_length;
	t_vec3	cam_right;
	t_vec3	cam_up;

	aspect_ratio = (double)width / (double)height;
	focal_length = 1.0;
	viewport_height = 2.0 * tan((cam->fov * M_PI / 180.0) / 2.0) * focal_length;
	viewport_width = viewport_height * aspect_ratio;
	cam_right = get_camera_right(cam->dir);
	cam_up = get_camera_up(cam->dir, cam_right);
	cam->viewport_u = vec_scale(viewport_width, cam_right);
	cam->viewport_v = vec_scale(-viewport_height, cam_up);
	cam->viewport_upper_left = vec_add(cam->position,
			vec_sub(vec_scale(focal_length, cam->dir),
				vec_add(vec_scale(0.5, cam->viewport_u),
					vec_scale(0.5, cam->viewport_v))));
	cam->pixel_delta_u = vec_scale(1.0 / width, cam->viewport_u);
	cam->pixel_delta_v = vec_scale(1.0 / height, cam->viewport_v);
}

t_ray	get_camera_ray(t_cam *cam, int x, int y)
{
	t_ray	ray;
	t_vec3	pixel_center;

	pixel_center = vec_add(cam->viewport_upper_left,
			vec_add(vec_scale(x + 0.5, cam->pixel_delta_u),
				vec_scale(y + 0.5, cam->pixel_delta_v)));
	ray.origin = cam->position;
	ray.direction = vec_normalize(vec_sub(pixel_center, cam->position));
	return (ray);
}
