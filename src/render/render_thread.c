/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 00:00:00 by abendrih          #+#    #+#             */
/*   Updated: 2025/12/19 21:53:00 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "ray.h"
#include "render.h"
#include <pthread.h>

static void	render_thread_row(t_render_task *task, int y)
{
	t_ray	ray;
	t_color	color;
	int		x;

	x = 0;
	while (x < WIDTH)
	{
		ray = get_camera_ray(&((t_scene *)task->scene)->camera, x, y);
		color = trace_ray(ray, (t_scene *)task->scene);
		put_pixel(&((t_mlx *)task->mlx)->img, x, y, rgb_to_int(color.r, color.g,
				color.b));
		x++;
	}
}

static void	*render_thread(void *arg)
{
	t_render_task	*task;
	int				y;

	task = (t_render_task *)arg;
	y = task->y_start;
	while (y < task->y_end)
	{
		render_thread_row(task, y);
		y++;
	}
	return (NULL);
}

static void	init_thread_task(t_render_task *task, t_mlx *mlx, t_scene *scene,
		int i)
{
	int	rows_per_thread;

	rows_per_thread = HEIGHT / NUM_THREADS;
	task->mlx = mlx;
	task->scene = scene;
	task->y_start = i * rows_per_thread;
	if (i == NUM_THREADS - 1)
		task->y_end = HEIGHT;
	else
		task->y_end = (i + 1) * rows_per_thread;
	task->scale = 1;
}

void	render_scene_threaded(t_scene *scene, t_mlx *mlx)
{
	pthread_t		threads[NUM_THREADS];
	t_render_task	tasks[NUM_THREADS];
	int				i;

	setup_camera(&scene->camera, WIDTH, HEIGHT);
	i = 0;
	while (i < NUM_THREADS)
	{
		init_thread_task(&tasks[i], mlx, scene, i);
		pthread_create(&threads[i], NULL, render_thread, &tasks[i]);
		i++;
	}
	i = 0;
	while (i < NUM_THREADS)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img.img_ptr, 0, 0);
	draw_hud(mlx, scene);
}
