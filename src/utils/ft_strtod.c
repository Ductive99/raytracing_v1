/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtod.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abendrih <abendrih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 00:00:00 by abendrih          #+#    #+#             */
/*   Updated: 2025/12/17 20:02:01 by abendrih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#include <stdio.h>
#include <stdbool.h>

/**
 * ft_strtod - converts the initial portion of a string to double
 *
 * @nptr: String to be converted to double
 * @endptr: If not NULL, stores the address of the first invalid character
 *
 * Parses the string nptr and converts it to a double value.
 * Handles optional leading whitespace, optional sign (+/-),
 * integer part, optional decimal point and fractional part.
 *
 * Format: [whitespace][+/-][digits][.digits]
 *
 * Return: The converted double value, or 0.0 if no valid conversion
 *         could be performed. If endptr is not NULL, it points to the
 *         first character after the number.
 */
double	ft_strtod(const char *nptr, char **endptr)
{
	double	result;
	double	fraction;

	result = 0.0;
	auto int sign = 1;
	fraction = 1.0;
	if (!nptr)
		return (result);
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
		sign -= 2 * (*nptr++ == '-');
	while (ft_isdigit(*nptr))
		result = result * 10 + (*nptr++ - '0');
	if (*nptr == '.')
	{
		while (ft_isdigit(*++nptr))
		{
			fraction *= 0.1;
			result += (double)(*nptr - '0') *fraction;
		}
	}
	if (endptr)
		*endptr = (char *)nptr;
	return (result * sign);
}
