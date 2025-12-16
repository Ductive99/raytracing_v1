/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 00:00:00 by abendrih          #+#    #+#             */
/*   Updated: 2025/12/14 18:18:06 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * handle_keypress - Handle keyboard events
 * @keycode: The key code of the pressed key
 * @mlx: Pointer to MLX structure
 *
 * Currently handles:
 * - ESC key: Close the window and exit the program
 *
 * Return: 0 on success
 */
int	handle_keypress(int keycode, t_mlx *mlx)
{
	if (keycode == KEY_ESC)
	{
		cleanup_scene((t_scene *)mlx->scene);
		cleanup_mlx(mlx);
		exit(0);
	}
	return (0);
}

/**
 * handle_close - Handle window close event (red X button)
 * @mlx: Pointer to MLX structure
 *
 * This function is called when the user clicks the window's close button.
 * It properly cleans up all resources before exiting.
 *
 * Return: 0 on success
 */
int	handle_close(t_mlx *mlx)
{
	cleanup_scene((t_scene *)mlx->scene);
	cleanup_mlx(mlx);
	exit(0);
	return (0);
}
