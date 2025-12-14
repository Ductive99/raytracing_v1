/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 00:00:00 by abendrih          #+#    #+#             */
/*   Updated: 2025/12/14 17:59:19 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * render_test_pattern - Render a test pattern to verify MLX is working
 * @mlx: Pointer to MLX structure
 * @scene: Pointer to scene structure (for future use)
 *
 * This is a temporary function that renders a simple test pattern.
 * Replace this with actual raytracing calculations when ready.
 *
 * Current pattern: Gradient background with a circle in the center
 */
void	render_test_pattern(t_mlx *mlx, t_scene *scene)
{
	int	x;
	int	y;
	int	color;
	int	center_x;
	int	center_y;
	int	dx;
	int	dy;
	int	dist_sq;

	(void)scene;
	center_x = WIN_WIDTH / 2;
	center_y = WIN_HEIGHT / 2;
	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			dx = x - center_x;
			dy = y - center_y;
			dist_sq = dx * dx + dy * dy;
			if (dist_sq < 100 * 100)
				color = rgb_to_int(255, 0, 0);
			else
			{
				int r = (x * 255) / WIN_WIDTH;
				int b = (y * 255) / WIN_HEIGHT;
				color = rgb_to_int(r, 50, b);
			}
			put_pixel(&mlx->img, x, y, color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr,
		mlx->img.img_ptr, 0, 0);
}
