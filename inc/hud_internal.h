/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_internal.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 00:00:00 by abendrih          #+#    #+#             */
/*   Updated: 2025/12/19 18:27:44 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HUD_INTERNAL_H
# define HUD_INTERNAL_H

# include "minirt.h"

// Global variables (extern)
extern t_button	g_buttons[NUM_BUTTONS];
extern t_button	g_light_btns[MAX_LIGHTS];
extern int		g_num_lights;

// hud_draw.c
void			hud_draw_rect(t_img *img, int x, int y, int w, int h,
					int color);
void			hud_draw_border(t_img *img, int x, int y, int w, int h,
					int color);
void			hud_draw_panel_bg(t_mlx *mlx);
void			hud_draw_section(t_mlx *mlx, int y, char *title);
void			hud_draw_button(t_mlx *mlx, t_button *btn);

// hud_buttons.c
void			hud_init_button(int idx, int x, int y, int action, char *label);
void			hud_init_buttons(void);
void			hud_draw_btn_labels(t_mlx *mlx);
void			hud_draw_all_buttons(t_mlx *mlx);
void			hud_draw_light_buttons(t_mlx *mlx, t_scene *scene);

// hud_click.c
int				hud_do_move(t_scene *scene, int action);
int				hud_do_rotate(t_scene *scene, int action);
int				hud_do_other(t_scene *scene, int action);
int				hud_check_light_click(int x, int y, t_scene *scene);

// hud.c
void			hud_count_lights(t_scene *scene);
char			*hud_get_selection_name(t_scene *scene);
void			hud_select_light_by_idx(t_scene *scene, int idx);

#endif /* HUD_INTERNAL_H */
