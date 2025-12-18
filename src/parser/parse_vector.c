/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_vector.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <souhailelhoussain@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 00:00:00 by abendrih          #+#    #+#             */
/*   Updated: 2025/12/18 03:14:44 by esouhail         ###   ########.fr       */
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

t_parse_status is_normalized(t_vec3 v)
{
    float len_squared = (v.x * v.x) + (v.y * v.y) + (v.z * v.z);

    if (fabs(len_squared - 1.0f) < 0.001)
        return (PARSE_SUCCESS);
    return (PARSE_ERROR);
}
