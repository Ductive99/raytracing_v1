/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_fast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 18:58:30 by abendrih          #+#    #+#             */
/*   Updated: 2025/12/19 21:53:00 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "ray.h"
#include "render.h"
#include <pthread.h>

static void	fill_block(t_mlx *mlx, t_rect pos, int pixel_color)
{
	int	i;
	int	j;

	i = 0;
	while (i < pos.h && (pos.y + i) < HEIGHT)
	{
		j = 0;
		while (j < pos.w && (pos.x + j) < WIDTH)
		{
			put_pixel(&mlx->img, pos.x + j, pos.y + i, pixel_color);
			j++;
		}
		i++;
	}
}

static void	render_pixel_block(t_render_task *task, int x, int y)
{
	t_ray	ray;
	t_color	color;
	int		pixel_color;

	ray = get_camera_ray(&((t_scene *)task->scene)->camera, x, y);
	color = trace_ray(ray, (t_scene *)task->scene);
	pixel_color = rgb_to_int(color.r, color.g, color.b);
	fill_block((t_mlx *)task->mlx, (t_rect){x, y, task->scale, task->scale},
		pixel_color);
}

void	render_scene_fast(t_scene *scene, t_mlx *mlx, int scale)
{
	t_render_task	task;
	int				x;
	int				y;

	setup_camera(&scene->camera, WIDTH, HEIGHT);
	task.mlx = mlx;
	task.scene = scene;
	task.scale = scale;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			render_pixel_block(&task, x, y);
			x += scale;
		}
		y += scale;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img.img_ptr, 0, 0);
}
