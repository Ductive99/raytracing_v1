/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 15:34:44 by esouhail          #+#    #+#             */
/*   Updated: 2025/12/12 21:37:07 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * parse_ambient - parses ambient lighting configuration from scene file
 *
 * @split: Array of strings containing ambient light parameters
 *         Expected format: ["A", "ratio", "R,G,B"]
 * @scene: Scene structure to store the parsed ambient light
 *
 * Parses the ambient lighting element which defines global illumination.
 * Format: A <ratio> <color>
 * - ratio: Ambient lighting ratio in range [0.0, 1.0]
 * - color: RGB color values (e.g., "255,255,255")
 *
 * Only one ambient light is allowed per scene.
 *
 * Return: PARSE_SUCCESS if parsing succeeds, PARSE_ERROR on failure
 */
t_parse_status	parse_ambient(char **split, t_scene *scene)
{
	char	*endptr;

	if (scene->ambient.ratio > 0.0)
		return (print_err("Duplicate ambient light detected"), PARSE_ERROR);
	if (count_split(split) != 3)
		return (print_err("Invalid number of ambient light parameters"),
			PARSE_ERROR);
	scene->ambient.ratio = ft_strtod(split[1], &endptr);
	if (*endptr != '\0')
		return (print_err("Invalid ambient ratio format"), PARSE_ERROR);
	if (scene->ambient.ratio < 0.0 || scene->ambient.ratio > 1.0)
		return (print_err("Ambient ratio must be in [0.0, 1.0]"), PARSE_ERROR);
	if (parse_color(split[2], &scene->ambient.color) == PARSE_ERROR)
		return (print_err("Invalid ambient color format"), PARSE_ERROR);
	return (PARSE_SUCCESS);
}
