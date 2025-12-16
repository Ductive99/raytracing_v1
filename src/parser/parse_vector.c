/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_vector.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 00:00:00 by abendrih          #+#    #+#             */
/*   Updated: 2025/12/12 21:34:48 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * parse_vector - Parse 3D vector from string "x,y,z"
 */
t_parse_status	parse_vector(char *str, t_vec3 *vec)
{
	char	**coords;
	char	*endptr;

	coords = ft_split(str, ",");
	if (!coords || count_split(coords) != 3)
		return (free_split(coords), PARSE_ERROR);
	vec->x = ft_strtod(coords[0], &endptr);
	if (*endptr != '\0')
		return (free_split(coords), PARSE_ERROR);
	vec->y = ft_strtod(coords[1], &endptr);
	if (*endptr != '\0')
		return (free_split(coords), PARSE_ERROR);
	vec->z = ft_strtod(coords[2], &endptr);
	if (*endptr != '\0')
		return (free_split(coords), PARSE_ERROR);
	free_split(coords);
	return (PARSE_SUCCESS);
}

/**
 * check_normalized_vector - Verify vector is normalized (length ~1.0)
 */
t_parse_status	check_normalized_vector(t_vec3 *vec)
{
	double	len;

	len = sqrt(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
	if (len < 0.99 || len > 1.01)
		return (PARSE_ERROR);
	return (PARSE_SUCCESS);
}
