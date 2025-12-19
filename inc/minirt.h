/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 10:29:17 by esouhail          #+#    #+#             */
/*   Updated: 2025/12/19 16:16:29 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../lib/minilibx-linux/mlx.h"
# include "structs.h"
# include <fcntl.h>
# include <math.h>
# include <pthread.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

// Window constants
# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define WIN_TITLE "miniRT"

// Key codes for Linux
# define KEY_ESC 65307
# define KEY_LEFT 65361
# define KEY_UP 65362
# define KEY_RIGHT 65363
# define KEY_DOWN 65364
# define KEY_PLUS 61
# define KEY_MINUS 45
# define KEY_R 114
# define KEY_W 119
# define KEY_S 115
# define KEY_A 97
# define KEY_D 100
# define KEY_Q 113
# define KEY_E 101

// Mouse buttons
# define MOUSE_LEFT 1
# define MOUSE_RIGHT 3
# define MOUSE_SCROLL_UP 4
# define MOUSE_SCROLL_DOWN 5

// Transform constants
# define MOVE_SPEED 0.5
# define ROTATE_SPEED 5.0
# define RESIZE_SPEED 0.2

// Render modes
# define RENDER_FULL 1
# define RENDER_FAST 4

// Multi-threading
# define NUM_THREADS 8

// Parsing
int				parse_scene(char *filename, t_scene *scene);

t_parse_status	parse_ambient(char **split, t_scene *scene);
t_parse_status	parse_camera(char **split, t_scene *scene);
t_parse_status	parse_color(char *str, t_color *color);
t_parse_status	parse_vector(char *str, t_vec3 *vec);
t_parse_status	parse_light(char **split, t_scene *scene);
t_parse_status	parse_plane(char **split, t_scene *scene);
t_parse_status	parse_sphere(char **split, t_scene *scene);
t_parse_status	parse_cylinder(char **split, t_scene *scene);
t_parse_status	parse_cone(char **split, t_scene *scene);
t_parse_status	is_normalized(t_vec3 v);

// Utils

size_t			ft_strlen(const char *s);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*get_next_line(int fd);

int				print_err(char *msg);

int				ft_isspace(int c);
int				ft_isdigit(int c);

void			free_split(char **split);
char			**ft_split(char const *s, const char *charset);
void			*ft_memcpy(void *dest, const void *src, size_t n);
size_t			count_split(char **split);

double			ft_strtod(const char *str, char **endptr);
int				ft_atoi(const char *str);

t_list			*ft_lstnew(void *content);
void			ft_lstadd_back(t_list **lst, t_list *new);
void			ft_lstclear(t_list **lst, void (*del)(void *));

// MLX functions

int				init_mlx(t_mlx *mlx);
void			cleanup_mlx(t_mlx *mlx);
void			cleanup_scene(t_scene *scene);
int				handle_keypress(int keycode, t_mlx *mlx);
int				handle_close(t_mlx *mlx);
int				handle_mouse(int button, int x, int y, t_mlx *mlx);
void			put_pixel(t_img *img, int x, int y, int color);
int				rgb_to_int(int r, int g, int b);
void			render_test_pattern(t_mlx *mlx, t_scene *scene);

// Selection
void			select_object(t_scene *scene, int x, int y);
void			deselect_object(t_scene *scene);
// t_hit			get_hit_at_pixel(t_scene *scene, int x, int y);

int				clamp(int value);
t_color			add_colors(t_color c1, t_color c2);
t_color			scale_color(t_color c, double intensity);
t_color			calculate_lighting(t_scene *scene, t_vec3 hit_point,
					t_vec3 normal, t_color obj_color, t_vec3 ray_dir);
int				is_in_shadow(t_scene *scene, t_light *light, t_vec3 hit_point,
					t_vec3 normal);
t_color			get_specular(t_light *light, t_vec3 hit_point, t_vec3 normal,
					t_vec3 view_dir);
int				clamp(int value);
t_color			add_colors(t_color c1, t_color c2);
t_color			scale_color(t_color c, double intensity);
int				is_in_shadow(t_scene *scene, t_light *light, t_vec3 hit_point,
					t_vec3 normal);

// Transform functions
void			translate_selection(t_scene *scene, t_vec3 delta);
void			translate_camera(t_scene *scene, t_vec3 delta);
void			rotate_selection(t_scene *scene, t_vec3 axis, double angle);
void			rotate_camera(t_scene *scene, t_vec3 axis, double angle);
void			resize_selection(t_scene *scene, double factor);

// Render functions
void			render_scene_fast(t_scene *scene, t_mlx *mlx, int scale);
void			render_scene_threaded(t_scene *scene, t_mlx *mlx);
int				handle_keyrelease(int keycode, t_mlx *mlx);

// HUD
void			draw_hud(t_mlx *mlx, t_scene *scene);
int				handle_hud_click(int x, int y, t_scene *scene);
void			rotate_hud(t_scene *scene, t_vec3 axis, double angle);

t_color			get_checker_color(double u, double v, t_color c1, t_color c2);
void			get_plane_uv(t_vec3 hit_point, double *u, double *v);
void			get_sphere_uv(t_vec3 normal, double *u, double *v);
void			get_cylinder_uv(t_cylinder *cy, t_vec3 hit_point, double *u,
					double *v);
void			get_cone_uv(t_cone *cone, t_vec3 hit_point, double *u,
					double *v);

#endif /* MINIRT_H */
