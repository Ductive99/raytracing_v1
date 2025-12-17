/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <souhailelhoussain@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 00:00:00 by abendrih          #+#    #+#             */
/*   Updated: 2025/12/17 14:49:08 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_parse_status	parse_camera(char **split, t_scene *scene)
{
	char	*endptr;

	if (scene->camera.fov != 0.0)
		return (print_err("Duplicate camera detected"), PARSE_ERROR);
	if (count_split(split) != 4)
		return (print_err("Invalid camera parameters"), PARSE_ERROR);
	if (parse_vector(split[1], &scene->camera.position) == PARSE_ERROR)
		return (print_err("Invalid camera position"), PARSE_ERROR);
	if (parse_vector(split[2], &scene->camera.dir) == PARSE_ERROR)
		return (print_err("Invalid camera direction"), PARSE_ERROR);
	if (check_normalized_vector(&scene->camera.dir) == PARSE_ERROR)
		return (print_err("Camera direction must be normalized"), PARSE_ERROR);
	scene->camera.fov = ft_strtod(split[3], &endptr);
	if (*endptr != '\0')
		return (print_err("Invalid FOV format"), PARSE_ERROR);
	if (scene->camera.fov < 0.0 || scene->camera.fov > 180.0)
		return (print_err("FOV must be in [0, 180]"), PARSE_ERROR);
	return (PARSE_SUCCESS);
}
