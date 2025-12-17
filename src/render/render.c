/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <souhailelhoussain@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 12:11:53 by esouhail          #+#    #+#             */
/*   Updated: 2025/12/17 16:38:10 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "minirt.h"
#include "ray.h"
#include "render.h"
#include <stdio.h>

void	render_scene(t_scene *scene, t_mlx *mlx)
{
	int		x;
	int		y;
	t_ray	ray;
	t_color	color;
	
	printf("=== RENDER DEBUG ===\n");
	printf("Resolution: %dx%d\n", WIDTH, HEIGHT);
	printf("Camera pos: (%.2f, %.2f, %.2f)\n", 
		scene->camera.position.x, scene->camera.position.y, scene->camera.position.z);
	printf("Camera dir: (%.2f, %.2f, %.2f)\n",
		scene->camera.dir.x, scene->camera.dir.y, scene->camera.dir.z);
	printf("Camera FOV: %.2f\n", scene->camera.fov);
	
	int sphere_count = 0;
	t_list *node = scene->spheres;
	while (node)
	{
		sphere_count++;
		node = node->next;
	}
	printf("Spheres in scene: %d\n", sphere_count);
	
	node = scene->spheres;
	int i = 1;
	while (node)
	{
		t_sphere *sp = (t_sphere *)node->obj;
		printf("Sphere %d center: (%.2f, %.2f, %.2f)\n", i, sp->center.x, sp->center.y, sp->center.z);
		printf("Sphere %d diameter: %.2f\n", i, sp->diameter);
		printf("Sphere %d color: RGB(%d, %d, %d)\n", i, sp->color.r, sp->color.g, sp->color.b);
		node = node->next;
		i++;
	}    setup_camera(&scene->camera, WIDTH, HEIGHT);
	printf("Camera setup complete\n");
	
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			ray = get_camera_ray(&scene->camera, x, y);
			
			if (x == WIDTH/2 && y == HEIGHT/2)
			{
				printf("\n=== CENTER PIXEL ===\n");
				printf("Ray origin: (%.2f, %.2f, %.2f)\n", 
					ray.origin.x, ray.origin.y, ray.origin.z);
				printf("Ray direction: (%.2f, %.2f, %.2f)\n",
					ray.direction.x, ray.direction.y, ray.direction.z);
			}
			
			color = trace_ray(ray, scene);
			
			if (x == WIDTH/2 && y == HEIGHT/2)
				printf("Color: RGB(%d, %d, %d)\n", color.r, color.g, color.b);
			
			put_pixel(&mlx->img, x, y, rgb_to_int(color.r, color.g, color.b));
			
			x++;
		}
		y++;
	}
	
	printf("=== RENDER COMPLETE ===\n");
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img.img_ptr, 0, 0);
}
