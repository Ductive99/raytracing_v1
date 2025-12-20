/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <souhailelhoussain@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 00:00:00 by abendrih          #+#    #+#             */
/*   Updated: 2025/12/20 18:18:13 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * init_mlx - Initialize MLX connection, window and image buffer
 * @mlx: Pointer to MLX structure to initialize
 *
 * This function:
 * 1. Creates MLX connection
 * 2. Creates a window with specified dimensions
 * 3. Creates an image buffer for pixel manipulation
 * 4. Gets the memory address of the image buffer
 *
 * Return: 0 on success, 1 on error
 */
int	init_mlx(t_mlx *mlx)
{
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
	{
		print_err("Error: Failed to initialize MLX\n");
		return (1);
	}
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WIDTH, HEIGHT, WIN_TITLE);
	if (!mlx->win_ptr)
	{
		print_err("Error: Failed to create window\n");
		mlx_destroy_display(mlx->mlx_ptr);
		return (free(mlx->mlx_ptr), 1);
	}
	mlx->img.img_ptr = mlx_new_image(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	if (!mlx->img.img_ptr)
	{
		print_err("Error: Failed to create image\n");
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
		mlx_destroy_display(mlx->mlx_ptr);
		return (free(mlx->mlx_ptr), 1);
	}
	mlx->img.addr = mlx_get_data_addr(mlx->img.img_ptr,
			&mlx->img.bits_per_pixel, &mlx->img.line_len, &mlx->img.endian);
	mlx->hud.initialized = 0;
	return (0);
}
