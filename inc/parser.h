/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <souhailelhoussain@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 17:22:19 by esouhail          #+#    #+#             */
/*   Updated: 2025/12/19 17:24:38 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "structs.h"

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

#endif
