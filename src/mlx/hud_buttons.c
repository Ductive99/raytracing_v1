/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_buttons.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 00:00:00 by abendrih          #+#    #+#             */
/*   Updated: 2025/12/19 21:12:37 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hud_internal.h"

void	hud_draw_btn_labels(t_mlx *mlx)
{
	int	i;
	int	offset_x;
	int	text_len;

	i = 0;
	while (i < NUM_BUTTONS)
	{
		text_len = ft_strlen(mlx->hud.buttons[i].label) * 6;
		offset_x = (mlx->hud.buttons[i].w - text_len) / 2;
		if (offset_x < 4)
			offset_x = 4;
		mlx_string_put(mlx->mlx_ptr, mlx->win_ptr,
			mlx->hud.buttons[i].x + offset_x,
			mlx->hud.buttons[i].y + 17, 0xFF88FF, mlx->hud.buttons[i].label);
		i++;
	}
}

void	hud_draw_all_buttons(t_mlx *mlx)
{
	int	i;

	i = 0;
	while (i < NUM_BUTTONS)
	{
		hud_draw_button(mlx, &mlx->hud.buttons[i]);
		i++;
	}
}

static void	hud_draw_light_sel(t_mlx *mlx, int i, int sel)
{
	if (sel)
		hud_draw_rect(&mlx->img, (t_rect){mlx->hud.light_btns[i].x - 2,
			mlx->hud.light_btns[i].y - 2, mlx->hud.light_btns[i].w + 4,
			mlx->hud.light_btns[i].h + 4}, 0xFFAA00);
	hud_draw_button(mlx, &mlx->hud.light_btns[i]);
}

void	hud_draw_light_buttons(t_mlx *mlx, t_scene *scene)
{
	int		i;
	int		sel;
	t_list	*lst;
	char	num[2];

	i = 0;
	lst = scene->lights;
	while (i < mlx->hud.num_lights)
	{
		sel = (scene->selection.type == OBJ_LIGHT
				&& scene->selection.object == lst->obj);
		hud_draw_light_sel(mlx, i, sel);
		num[0] = '1' + i;
		num[1] = '\0';
		mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, mlx->hud.light_btns[i].x
			+ 10, mlx->hud.light_btns[i].y + 17, 0xFF88FF, "Light");
		mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, mlx->hud.light_btns[i].x
			+ 50, mlx->hud.light_btns[i].y + 17, 0xFF88FF, num);
		lst = lst->next;
		i++;
	}
}
