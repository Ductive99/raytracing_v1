/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <esouhail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 04:28:52 by esouhail          #+#    #+#             */
/*   Updated: 2025/10/18 04:30:58 by esouhail         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

size_t	count_split(char **split)
{
	size_t	len;

	len = 0;
	if (!split || !split[0])
		return (0);
	while (split[len])
		len++;
	return (len);
}
