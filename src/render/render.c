/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 12:11:53 by esouhail          #+#    #+#             */
/*   Updated: 2025/12/19 21:51:29 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "ray.h"
#include "render.h"
#include "structs.h"

static void	render_row(t_scene *scene, t_mlx *mlx, int y)
{
	int		x;
	t_ray	ray;
	t_color	color;

	x = 0;
	while (x < WIDTH)
	{
		ray = get_camera_ray(&scene->camera, x, y);
		color = trace_ray(ray, scene);
		put_pixel(&mlx->img, x, y, rgb_to_int(color.r, color.g, color.b));
		x++;
	}
}

void	render_scene(t_scene *scene, t_mlx *mlx)
{
	int	y;

	setup_camera(&scene->camera, WIDTH, HEIGHT);
	y = 0;
	while (y < HEIGHT)
	{
		render_row(scene, mlx, y);
		y++;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img.img_ptr, 0, 0);
	draw_hud(mlx, scene);
}
