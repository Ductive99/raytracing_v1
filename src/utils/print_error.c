/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esouhail <esouhail@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 10:37:46 by esouhail          #+#    #+#             */
/*   Updated: 2025/10/16 03:36:53 by esouhail         ###   ########.fr       */
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
int	print_err(char *msg, int format)
{
	if (format)
		write(2, "Error: ", 7);
	write(2, msg, ft_strlen(msg));
	if (format)
		write(2, "\n", 1);
	return (1);
}
