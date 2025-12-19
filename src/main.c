/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <esouhail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 00:00:00 by abendrih          #+#    #+#             */
/*   Updated: 2025/12/19 21:56:59 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "ray.h"
#include "render.h"

/**
 * init_scene - Initialize scene with default values
 * @scene: Pointer to scene structure
 */
static void	init_scene(t_scene *scene)
{
	scene->ambient.ratio = -1.0;
	scene->camera.fov = 0.0;
	scene->lights = NULL;
	scene->spheres = NULL;
	scene->planes = NULL;
	scene->cylinders = NULL;
	scene->cones = NULL;
	scene->selection.type = OBJ_NONE;
	scene->selection.object = NULL;
}

/**
 * setup_hooks - Setup all MLX event hooks
 * @mlx: Pointer to MLX structure
 *
 * This function registers:
 * - Key press events (for ESC key)
 * - Key release events (for full render after transform)
 * - Window close event (red X button)
 * - Mouse click events (for object selection)
 */
static void	setup_hooks(t_mlx *mlx)
{
	mlx_do_key_autorepeatoff(mlx->mlx_ptr);
	mlx_hook(mlx->win_ptr, 2, 1L << 0, handle_keypress, mlx);
	mlx_hook(mlx->win_ptr, 3, 1L << 1, handle_keyrelease, mlx);
	mlx_hook(mlx->win_ptr, 17, 0, handle_close, mlx);
	mlx_mouse_hook(mlx->win_ptr, handle_mouse, mlx);
}

/**
 * main - Entry point of the program
 * @argc: Number of arguments
 * @argv: Array of arguments
 *
 * Process:
 * 1. Parse the scene file
 * 2. Initialize MLX (window and image buffer)
 * 3. Setup event hooks
 * 4. Enter MLX event loop
 * 5. Cleanup on exit
 *
 * Return: 0 on success, 1 on error
 */
int	main(int argc, char **argv)
{
	t_scene	scene;
	t_mlx	mlx;

	if (argc != 2)
	{
		printf("Usage: %s <scene.rt>\n", argv[0]);
		return (1);
	}
	init_scene(&scene);
	if (parse_scene(argv[1], &scene) == PARSE_ERROR)
	{
		cleanup_scene(&scene);
		printf("Error: Failed to parse scene\n");
		return (cleanup_scene(&scene), 1);
	}
	if (init_mlx(&mlx) != 0)
		return (cleanup_scene(&scene), 1);
	mlx.scene = &scene;
	render_scene(&scene, &mlx);
	setup_hooks(&mlx);
	mlx_loop(mlx.mlx_ptr);
	cleanup_mlx(&mlx);
	cleanup_scene(&scene);
	return (0);
}
