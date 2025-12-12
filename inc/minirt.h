/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 10:29:17 by esouhail          #+#    #+#             */
/*   Updated: 2025/12/12 18:05:28 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "structs.h"
# include <fcntl.h>
# include <math.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

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

#endif /* MINIRT_H */
