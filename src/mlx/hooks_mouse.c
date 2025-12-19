/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_mouse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 00:00:00 by abendrih          #+#    #+#             */
/*   Updated: 2025/12/19 18:54:52 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "render.h"

int	handle_mouse(int button, int x, int y, t_mlx *mlx)
{
	t_scene	*scene;
	int		hud_result;

	scene = (t_scene *)mlx->scene;
	if (button == MOUSE_LEFT)
	{
		hud_result = handle_hud_click(x, y, scene);
		if (hud_result == 2)
		{
			cleanup_scene(scene);
			cleanup_mlx(mlx);
			exit(0);
		}
		if (hud_result == 1)
			return (render_scene_threaded(scene, mlx), 0);
		select_object(scene, x, y);
		render_scene_threaded(scene, mlx);
	}
	else if (button == MOUSE_RIGHT)
	{
		deselect_object(scene);
		render_scene_threaded(scene, mlx);
	}
	return (0);
}

int	handle_close(t_mlx *mlx)
{
	cleanup_scene((t_scene *)mlx->scene);
	cleanup_mlx(mlx);
	exit(0);
	return (0);
}
