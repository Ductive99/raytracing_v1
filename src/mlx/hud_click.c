/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_click.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 00:00:00 by abendrih          #+#    #+#             */
/*   Updated: 2025/12/19 21:09:34 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hud_internal.h"

int	hud_do_move(t_scene *scene, int action)
{
	t_vec3	local;
	t_vec3	delta;

	local = (t_vec3){0, 0, 0};
	if (action == BTN_MOVE_LEFT)
		local.x = -MOVE_SPEED;
	else if (action == BTN_MOVE_RIGHT)
		local.x = MOVE_SPEED;
	else if (action == BTN_MOVE_FWD)
		local.z = MOVE_SPEED;
	else if (action == BTN_MOVE_BACK)
		local.z = -MOVE_SPEED;
	else if (action == BTN_MOVE_UP)
		local.y = MOVE_SPEED;
	else if (action == BTN_MOVE_DOWN)
		local.y = -MOVE_SPEED;
	else
		return (0);
	delta = get_camera_delta(&scene->camera, local);
	if (scene->selection.type != OBJ_NONE)
		translate_selection(scene, delta);
	else
		translate_camera(scene, delta);
	return (1);
}

int	hud_do_rotate(t_scene *scene, int action)
{
	if (action == BTN_ROT_LEFT)
		rotate_hud(scene, (t_vec3){0, 1, 0}, ROTATE_SPEED);
	else if (action == BTN_ROT_RIGHT)
		rotate_hud(scene, (t_vec3){0, 1, 0}, -ROTATE_SPEED);
	else if (action == BTN_ROT_UP)
		rotate_hud(scene, (t_vec3){1, 0, 0}, ROTATE_SPEED);
	else if (action == BTN_ROT_DOWN)
		rotate_hud(scene, (t_vec3){1, 0, 0}, -ROTATE_SPEED);
	else
		return (0);
	return (1);
}

int	hud_do_other(t_scene *scene, int action)
{
	if (action == BTN_SIZE_UP)
		resize_selection(scene, 1.0 + RESIZE_SPEED);
	else if (action == BTN_SIZE_DOWN)
		resize_selection(scene, 1.0 - RESIZE_SPEED);
	else if (action == BTN_DESELECT)
		deselect_object(scene);
	else if (action == BTN_QUIT)
		return (2);
	else
		return (0);
	return (1);
}

int	hud_check_light_click(int x, int y, t_mlx *mlx, t_scene *scene)
{
	int			i;
	t_button	*btn;

	i = 0;
	while (i < mlx->hud.num_lights)
	{
		btn = &mlx->hud.light_btns[i];
		if (x >= btn->x && x < btn->x + btn->w && y >= btn->y && y < btn->y
			+ btn->h)
		{
			hud_select_light_by_idx(scene, i);
			return (1);
		}
		i++;
	}
	return (0);
}

int	handle_hud_click(int x, int y, t_mlx *mlx, t_scene *scene)
{
	int			i;
	int			ret;
	t_button	*btn;

	if (hud_check_light_click(x, y, mlx, scene))
		return (1);
	i = 0;
	while (i < NUM_BUTTONS)
	{
		btn = &mlx->hud.buttons[i];
		if (x >= btn->x && x < btn->x + btn->w && y >= btn->y && y < btn->y
			+ btn->h)
		{
			ret = hud_do_move(scene, btn->action);
			if (ret)
				return (ret);
			ret = hud_do_rotate(scene, btn->action);
			if (ret)
				return (ret);
			return (hud_do_other(scene, btn->action));
		}
		i++;
	}
	return (0);
}
