/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 00:00:00 by abendrih          #+#    #+#             */
/*   Updated: 2025/12/12 21:37:07 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_parse_status	parse_cylinder(char **split, t_scene *scene)
{
	t_cylinder	*cylinder;
	char		*endptr;

	if (count_split(split) != 6)
		return (print_err("Invalid cylinder parameters"), PARSE_ERROR);
	cylinder = malloc(sizeof(t_cylinder));
	if (!cylinder)
		return (PARSE_ERROR);
	if (parse_vector(split[1], &cylinder->center) == PARSE_ERROR)
		return (free(cylinder), print_err("Invalid cylinder center"),
			PARSE_ERROR);
	if (parse_vector(split[2], &cylinder->axis) == PARSE_ERROR)
		return (free(cylinder), print_err("Invalid cylinder axis"),
			PARSE_ERROR);
	if (check_normalized_vector(&cylinder->axis) == PARSE_ERROR)
		return (free(cylinder), print_err("Cylinder axis must be normalized"),
			PARSE_ERROR);
	cylinder->diameter = ft_strtod(split[3], &endptr);
	if (*endptr != '\0')
		return (free(cylinder), print_err("Invalid cylinder diameter format"),
			PARSE_ERROR);
	cylinder->height = ft_strtod(split[4], &endptr);
	if (*endptr != '\0')
		return (free(cylinder), print_err("Invalid cylinder height format"),
			PARSE_ERROR);
	if (cylinder->diameter <= 0.0 || cylinder->height <= 0.0)
		return (free(cylinder),
			print_err("Cylinder dimensions must be positive"), PARSE_ERROR);
	if (parse_color(split[5], &cylinder->color) == PARSE_ERROR)
		return (free(cylinder), print_err("Invalid cylinder color"),
			PARSE_ERROR);
	ft_lstadd_back(&scene->cylinders, ft_lstnew(cylinder));
	return (PARSE_SUCCESS);
}
