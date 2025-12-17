/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 00:00:00 by abendrih          #+#    #+#             */
/*   Updated: 2025/12/12 21:37:07 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_parse_status	parse_light(char **split, t_scene *scene)
{
	t_light	*light;
	char	*endptr;

	if (count_split(split) != 4)
		return (print_err("Invalid light parameters"), PARSE_ERROR);
	light = malloc(sizeof(t_light));
	if (!light)
		return (PARSE_ERROR);
	if (parse_vector(split[1], &light->pos) == PARSE_ERROR)
		return (free(light), print_err("Invalid light position"), PARSE_ERROR);
	light->ratio = ft_strtod(split[2], &endptr);
	if (*endptr != '\0')
		return (free(light), print_err("Invalid light ratio format"),
			PARSE_ERROR);
	if (light->ratio < 0.0 || light->ratio > 1.0)
		return (free(light), print_err("Light ratio must be in [0.0, 1.0]"),
			PARSE_ERROR);
	if (parse_color(split[3], &light->color) == PARSE_ERROR)
		return (free(light), print_err("Invalid light color"), PARSE_ERROR);
	ft_lstadd_back(&scene->lights, ft_lstnew(light));
	return (PARSE_SUCCESS);
}
