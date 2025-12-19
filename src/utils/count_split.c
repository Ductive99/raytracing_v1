/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 04:28:52 by esouhail          #+#    #+#             */
/*   Updated: 2025/12/19 21:42:27 by abendrih         ###   ########.fr       */
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
