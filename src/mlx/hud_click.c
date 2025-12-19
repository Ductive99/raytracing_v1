/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_click.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 00:00:00 by abendrih          #+#    #+#             */
/*   Updated: 2025/12/19 18:27:44 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hud_internal.h"

int	hud_do_move(t_scene *scene, int action)
{
	t_vec3	delta;

	delta = (t_vec3){0, 0, 0};
	if (action == BTN_MOVE_LEFT)
		delta.x = -MOVE_SPEED;
	else if (action == BTN_MOVE_RIGHT)
		delta.x = MOVE_SPEED;
	else if (action == BTN_MOVE_FWD)
		delta.z = MOVE_SPEED;
	else if (action == BTN_MOVE_BACK)
		delta.z = -MOVE_SPEED;
	else if (action == BTN_MOVE_UP)
		delta.y = MOVE_SPEED;
	else if (action == BTN_MOVE_DOWN)
		delta.y = -MOVE_SPEED;
	else
		return (0);
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

int	hud_check_light_click(int x, int y, t_scene *scene)
{
	int	i;

	i = 0;
	while (i < g_num_lights)
	{
		if (x >= g_light_btns[i].x && x < g_light_btns[i].x + g_light_btns[i].w
			&& y >= g_light_btns[i].y && y < g_light_btns[i].y
			+ g_light_btns[i].h)
		{
			hud_select_light_by_idx(scene, i);
			return (1);
		}
		i++;
	}
	return (0);
}

int	handle_hud_click(int x, int y, t_scene *scene)
{
	int	i;
	int	act;
	int	ret;

	if (hud_check_light_click(x, y, scene))
		return (1);
	i = 0;
	while (i < NUM_BUTTONS)
	{
		if (x >= g_buttons[i].x && x < g_buttons[i].x + g_buttons[i].w
			&& y >= g_buttons[i].y && y < g_buttons[i].y + g_buttons[i].h)
		{
			act = g_buttons[i].action;
			ret = hud_do_move(scene, act);
			if (ret)
				return (ret);
			ret = hud_do_rotate(scene, act);
			if (ret)
				return (ret);
			return (hud_do_other(scene, act));
		}
		i++;
	}
	return (0);
}
