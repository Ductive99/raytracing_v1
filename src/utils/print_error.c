/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 10:37:46 by esouhail          #+#    #+#             */
/*   Updated: 2025/12/19 21:42:38 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * print_err - prints a message to stderr, with formatting (Error: <msg>\n)
 *
 * @msg: message to print
 *
 * Return: 1 always
 */
int	print_err(char *msg)
{
	int	ret;

	ret = write(2, "Error: ", 7);
	ret = write(2, msg, ft_strlen(msg));
	ret = write(2, "\n", 1);
	(void)ret;
	return (1);
}
