/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 00:00:00 by abendrih          #+#    #+#             */
/*   Updated: 2025/12/14 17:34:41 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * cleanup_scene - Free all allocated memory in the scene
 * @scene: Pointer to scene structure
 *
 * Properly frees all linked lists of objects in the scene.
 * This prevents memory leaks.
 */
void	cleanup_scene(t_scene *scene)
{
	if (scene->lights)
		ft_lstclear(&scene->lights, free);
	if (scene->spheres)
		ft_lstclear(&scene->spheres, free);
	if (scene->planes)
		ft_lstclear(&scene->planes, free);
	if (scene->cylinders)
		ft_lstclear(&scene->cylinders, free);
	free(scene->lights);
}

/**
 * cleanup_mlx - Clean up all MLX resources
 * @mlx: Pointer to MLX structure
 *
 * This function properly destroys all MLX resources in the correct order:
 * 1. Image buffer
 * 2. Window
 * 3. MLX display connection
 * 4. MLX instance
 *
 * This prevents memory leaks and ensures proper cleanup.
 */
void	cleanup_mlx(t_mlx *mlx)
{
	if (mlx->img.img_ptr)
	{
		mlx_destroy_image(mlx->mlx_ptr, mlx->img.img_ptr);
		mlx->img.img_ptr = NULL;
	}
	if (mlx->win_ptr)
	{
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
		mlx->win_ptr = NULL;
	}
	if (mlx->mlx_ptr)
	{
		mlx_destroy_display(mlx->mlx_ptr);
		free(mlx->mlx_ptr);
		mlx->mlx_ptr = NULL;
	}
}
