/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 00:00:00 by abendrih          #+#    #+#             */
/*   Updated: 2025/12/12 21:37:07 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_parse_status	parse_sphere(char **split, t_scene *scene)
{
	t_sphere	*sphere;
	char		*endptr;

	if (count_split(split) != 4)
		return (print_err("Invalid sphere parameters"), PARSE_ERROR);
	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		return (PARSE_ERROR);
	if (parse_vector(split[1], &sphere->center) == PARSE_ERROR)
		return (free(sphere), print_err("Invalid sphere center"), PARSE_ERROR);
	sphere->diameter = ft_strtod(split[2], &endptr);
	if (*endptr != '\0')
		return (free(sphere), print_err("Invalid sphere diameter format"),
			PARSE_ERROR);
	if (sphere->diameter <= 0.0)
		return (free(sphere), print_err("Sphere diameter must be positive"),
			PARSE_ERROR);
	if (parse_color(split[3], &sphere->color) == PARSE_ERROR)
		return (free(sphere), print_err("Invalid sphere color"), PARSE_ERROR);
	ft_lstadd_back(&scene->spheres, ft_lstnew(sphere));
	return (PARSE_SUCCESS);
}
