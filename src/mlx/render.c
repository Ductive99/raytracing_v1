/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 00:00:00 by abendrih          #+#    #+#             */
/*   Updated: 2025/12/19 19:46:56 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	get_test_color(int x, int y)
{
	int	dx;
	int	dy;
	int	dist_sq;

	dx = x - WIN_WIDTH / 2;
	dy = y - WIN_HEIGHT / 2;
	dist_sq = dx * dx + dy * dy;
	if (dist_sq < 100 * 100)
		return (rgb_to_int(255, 0, 0));
	return (rgb_to_int((x * 255) / WIN_WIDTH, 50, (y * 255) / WIN_HEIGHT));
}

void	render_test_pattern(t_mlx *mlx, t_scene *scene)
{
	int	x;
	int	y;

	(void)scene;
	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			put_pixel(&mlx->img, x, y, get_test_color(x, y));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img.img_ptr, 0, 0);
}
