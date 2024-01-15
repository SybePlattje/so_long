/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: splattje <splattje@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/04 16:10:30 by splattje      #+#    #+#                 */
/*   Updated: 2023/11/21 11:42:54 by splattje      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	integer;
	int	sign;
	int	index;

	integer = 0;
	sign = 1;
	index = 0;
	while (ft_iswhitespace(nptr[index]))
		index++;
	if (nptr[index] == '+' || nptr[index] == '-')
	{
		if (nptr[index] == '-')
			sign = -1;
		index++;
	}
	while (ft_isdigit(nptr[index]))
	{
		integer = integer * 10 + (nptr[index] - '0');
		index++;
	}
	return (integer * sign);
}
