/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <souhailelhoussain@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 10:29:17 by esouhail          #+#    #+#             */
/*   Updated: 2025/12/17 14:48:35 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../lib/minilibx-linux/mlx.h"
# include "structs.h"
# include <stdbool.h>
# include <fcntl.h>
# include <math.h>
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
t_parse_status	check_normalized_vector(t_vec3 *vec);

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
void			put_pixel(t_img *img, int x, int y, int color);
int				rgb_to_int(int r, int g, int b);
void			render_test_pattern(t_mlx *mlx, t_scene *scene);

// // Vector math functions

// t_vec3			vec_add(t_vec3 a, t_vec3 b);
// t_vec3			vec_sub(t_vec3 a, t_vec3 b);
// t_vec3			vec_scale(t_vec3 v, double scalar);
// double			vec_dot(t_vec3 a, t_vec3 b);
// double			vec_length(t_vec3 v);
// t_vec3			vec_normalize(t_vec3 v);
// t_vec3			vec_cross(t_vec3 a, t_vec3 b);

#endif /* MINIRT_H */
