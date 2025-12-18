/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 00:00:00 by abendrih          #+#    #+#             */
/*   Updated: 2025/12/18 07:18:31 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "render.h"
#include "vector_math.h"

static void	handle_move_keys(int keycode, t_scene *scene)
{
	t_vec3	delta;

	delta = (t_vec3){0, 0, 0};
	if (keycode == KEY_LEFT)
		delta.x = -MOVE_SPEED;
	else if (keycode == KEY_RIGHT)
		delta.x = MOVE_SPEED;
	else if (keycode == KEY_UP)
		delta.z = MOVE_SPEED;
	else if (keycode == KEY_DOWN)
		delta.z = -MOVE_SPEED;
	else if (keycode == KEY_W)
		delta.y = MOVE_SPEED;
	else if (keycode == KEY_S)
		delta.y = -MOVE_SPEED;
	if (scene->selection.type != OBJ_NONE)
		translate_selection(scene, delta);
	else
		translate_camera(scene, delta);
}

static void	handle_rotate_keys(int keycode, t_scene *scene)
{
	t_vec3	axis;
	double	angle;

	axis = (t_vec3){0, 1, 0};
	angle = ROTATE_SPEED;
	if (keycode == KEY_A)
		axis = (t_vec3){0, 1, 0};
	else if (keycode == KEY_D)
	{
		axis = (t_vec3){0, 1, 0};
		angle = -ROTATE_SPEED;
	}
	else if (keycode == KEY_Q)
		axis = (t_vec3){1, 0, 0};
	else if (keycode == KEY_E)
	{
		axis = (t_vec3){1, 0, 0};
		angle = -ROTATE_SPEED;
	}
	if (scene->selection.type != OBJ_NONE)
		rotate_selection(scene, axis, angle);
	else
		rotate_camera(scene, axis, angle);
}

static void	handle_resize_keys(int keycode, t_scene *scene)
{
	if (scene->selection.type == OBJ_NONE)
		return ;
	if (keycode == KEY_PLUS)
		resize_selection(scene, 1.0 + RESIZE_SPEED);
	else if (keycode == KEY_MINUS)
		resize_selection(scene, 1.0 - RESIZE_SPEED);
}

int	handle_keypress(int keycode, t_mlx *mlx)
{
	t_scene	*scene;

	scene = (t_scene *)mlx->scene;
	if (keycode == KEY_ESC)
	{
		cleanup_scene(scene);
		cleanup_mlx(mlx);
		exit(0);
	}
	if (keycode == KEY_LEFT || keycode == KEY_RIGHT || keycode == KEY_UP
		|| keycode == KEY_DOWN || keycode == KEY_W || keycode == KEY_S)
		handle_move_keys(keycode, scene);
	else if (keycode == KEY_A || keycode == KEY_D || keycode == KEY_Q
		|| keycode == KEY_E)
		handle_rotate_keys(keycode, scene);
	else if (keycode == KEY_PLUS || keycode == KEY_MINUS)
		handle_resize_keys(keycode, scene);
	else if (keycode == KEY_R)
		deselect_object(scene);
	setup_camera(&scene->camera, WIN_WIDTH, WIN_HEIGHT);
	render_scene(scene, mlx);
	return (0);
}

int	handle_mouse(int button, int x, int y, t_mlx *mlx)
{
	t_scene	*scene;

	scene = (t_scene *)mlx->scene;
	if (button == MOUSE_LEFT)
	{
		select_object(scene, x, y);
		render_scene(scene, mlx);
	}
	else if (button == MOUSE_RIGHT)
	{
		deselect_object(scene);
		render_scene(scene, mlx);
	}
	else if (button == MOUSE_SCROLL_UP)
	{
		if (scene->selection.type != OBJ_NONE)
			resize_selection(scene, 1.0 + RESIZE_SPEED);
		setup_camera(&scene->camera, WIN_WIDTH, WIN_HEIGHT);
		render_scene(scene, mlx);
	}
	else if (button == MOUSE_SCROLL_DOWN)
	{
		if (scene->selection.type != OBJ_NONE)
			resize_selection(scene, 1.0 - RESIZE_SPEED);
		setup_camera(&scene->camera, WIN_WIDTH, WIN_HEIGHT);
		render_scene(scene, mlx);
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
