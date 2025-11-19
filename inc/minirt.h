/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <esouhail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 10:29:17 by esouhail          #+#    #+#             */
/*   Updated: 2025/10/18 05:39:24 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "structs.h"
# include <fcntl.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>

typedef enum e_parse_status
{
	PARSE_SUCCESS = 0,
	PARSE_ERROR = 1
}				t_parse_status;

// Parsing

int				parse_scene(char *filename, t_scene *scene);

t_parse_status	parse_ambient(char **split, t_scene *scene);
t_parse_status	parse_camera(char **split, t_scene *scene);
t_parse_status	parse_color(char **split, t_scene *scene);
t_parse_status	parse_vector(char **split, t_scene *scene);
t_parse_status	parse_light(char **split, t_scene *scene);
t_parse_status	parse_plane(char **split, t_scene *scene);
t_parse_status	parse_sphere(char **split, t_scene *scene);
t_parse_status	parse_cylinder(char **split, t_scene *scene);

// Utils

size_t			ft_strlen(const char *s);

int				print_err(char *msg);

int				ft_isspace(int c);
int				ft_isdigit(int c);

void			free_split(char **split);
char			**ft_split(char const *s, const char *charset);
void			*ft_memcpy(void *dest, const void *src, size_t n);
size_t			count_split(char **split);

t_list			*ft_lstnew(void *content);
t_list			*ft_lstadd_back(t_list **lst, t_list *new);
t_list			*ft_lstclear(t_list **lst, void (*del)(void *));

#endif /* MINIRT_H */
