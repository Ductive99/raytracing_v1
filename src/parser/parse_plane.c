/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 00:00:00 by abendrih          #+#    #+#             */
/*   Updated: 2025/12/12 00:47:50 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_parse_status	parse_plane(char **split, t_scene *scene)
{
	t_plan	*plane;

	if (count_split(split) != 4)
		return (print_err("Invalid plane parameters"), PARSE_ERROR);
	plane = malloc(sizeof(t_plan));
	if (!plane)
		return (PARSE_ERROR);
	if (parse_vector(split[1], &plane->point) == PARSE_ERROR)
		return (free(plane), print_err("Invalid plane point"), PARSE_ERROR);
	if (parse_vector(split[2], &plane->normal) == PARSE_ERROR)
		return (free(plane), print_err("Invalid plane normal"), PARSE_ERROR);
	if (check_normalized_vector(&plane->normal) == PARSE_ERROR)
		return (free(plane), print_err("Plane normal must be normalized"),
			PARSE_ERROR);
	if (parse_color(split[3], &plane->color) == PARSE_ERROR)
		return (free(plane), print_err("Invalid plane color"), PARSE_ERROR);
	ft_lstadd_back(&scene->planes, ft_lstnew(plane));
	return (PARSE_SUCCESS);
}
