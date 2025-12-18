#include "minirt.h"
#include "ray.h"
#include "render.h"
#include <pthread.h>

static void	render_pixel_block(t_mlx *mlx, t_scene *scene, int x, int y,
		int scale)
{
	t_ray	ray;
	t_color	color;
	int		pixel_color;
	int		i;
	int		j;

	ray = get_camera_ray(&scene->camera, x, y);
	color = trace_ray(ray, scene);
	pixel_color = rgb_to_int(color.r, color.g, color.b);
	i = 0;
	while (i < scale && (y + i) < HEIGHT)
	{
		j = 0;
		while (j < scale && (x + j) < WIDTH)
		{
			put_pixel(&mlx->img, x + j, y + i, pixel_color);
			j++;
		}
		i++;
	}
}

void	render_scene_fast(t_scene *scene, t_mlx *mlx, int scale)
{
	int	x;
	int	y;

	setup_camera(&scene->camera, WIDTH, HEIGHT);
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			render_pixel_block(mlx, scene, x, y, scale);
			x += scale;
		}
		y += scale;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img.img_ptr, 0, 0);
}

static void	*render_thread(void *arg)
{
	t_render_task	*task;
	t_mlx			*mlx;
	t_scene			*scene;
	t_ray			ray;
	t_color			color;
	int				x;
	int				y;

	task = (t_render_task *)arg;
	mlx = (t_mlx *)task->mlx;
	scene = (t_scene *)task->scene;
	y = task->y_start;
	while (y < task->y_end)
	{
		x = 0;
		while (x < WIDTH)
		{
			ray = get_camera_ray(&scene->camera, x, y);
			color = trace_ray(ray, scene);
			put_pixel(&mlx->img, x, y, rgb_to_int(color.r, color.g, color.b));
			x++;
		}
		y++;
	}
	return (NULL);
}

void	render_scene_threaded(t_scene *scene, t_mlx *mlx)
{
	pthread_t		threads[NUM_THREADS];
	t_render_task	tasks[NUM_THREADS];
	int				rows_per_thread;
	int				i;

	setup_camera(&scene->camera, WIDTH, HEIGHT);
	rows_per_thread = HEIGHT / NUM_THREADS;
	i = 0;
	while (i < NUM_THREADS)
	{
		tasks[i].mlx = mlx;
		tasks[i].scene = scene;
		tasks[i].y_start = i * rows_per_thread;
		if (i == NUM_THREADS - 1)
			tasks[i].y_end = HEIGHT;
		else
			tasks[i].y_end = (i + 1) * rows_per_thread;
		tasks[i].scale = 1;
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
