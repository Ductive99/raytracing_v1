/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <esouhail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 22:00:00 by abendrih          #+#    #+#             */
/*   Updated: 2025/12/19 22:32:19 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "vector_math.h"

static t_parse_status	parse_cone_dimensions(char **split, t_cone *cone)
{
	char	*endptr;

	cone->angle = ft_strtod(split[3], &endptr);
	if (*endptr != '\0')
		return (print_err("Invalid cone angle format"), PARSE_ERROR);
	cone->height = ft_strtod(split[4], &endptr);
	if (*endptr != '\0')
		return (print_err("Invalid cone height format"), PARSE_ERROR);
	if (cone->angle <= 0.0 || cone->angle >= 90.0)
		return (print_err("Cone angle must be between 0 and 90"), PARSE_ERROR);
	if (cone->height <= 0.0)
		return (print_err("Cone height must be positive"), PARSE_ERROR);
	return (PARSE_SUCCESS);
}

t_parse_status	parse_cone(char **split, t_scene *scene)
{
	t_cone	*cone;

	if (count_split(split) != 6)
		return (print_err("Invalid cone parameters"), PARSE_ERROR);
	cone = malloc(sizeof(t_cone));
	if (!cone)
		return (PARSE_ERROR);
	if (parse_vector(split[1], &cone->apex) == PARSE_ERROR)
		return (free(cone), print_err("Invalid cone apex"), PARSE_ERROR);
	if (parse_vector(split[2], &cone->axis) == PARSE_ERROR)
		return (free(cone), print_err("Invalid cone axis"), PARSE_ERROR);
	cone->axis = vec_normalize(cone->axis);
	if (is_normalized(cone->axis) == PARSE_ERROR)
		return (free(cone), print_err("Cone axis must be normalized"),
			PARSE_ERROR);
	if (parse_cone_dimensions(split, cone) == PARSE_ERROR)
		return (free(cone), PARSE_ERROR);
	if (parse_color(split[5], &cone->color) == PARSE_ERROR)
		return (free(cone), print_err("Invalid cone color"), PARSE_ERROR);
	ft_lstadd_back(&scene->cones, ft_lstnew(cone));
	return (PARSE_SUCCESS);
}
