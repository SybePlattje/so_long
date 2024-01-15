/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_output.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: splattje <splattje@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/14 10:00:06 by splattje      #+#    #+#                 */
/*   Updated: 2023/11/15 15:09:49 by splattje      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar(va_list ap, char c, int inputplace)
{
	char	ch;

	if (inputplace == 1)
	{
		if (c == 'c')
		{
			ch = va_arg(ap, int);
			ft_putchar_fd(ch, 1);
			return (1);
		}
		else
		{
			ft_putchar_fd('%', 1);
			return (1);
		}
	}
	else
	{
		ft_putchar_fd(c, 1);
		return (1);
	}
}

int	ft_putstring(va_list ap)
{
	char	*str;

	str = NULL;
	str = va_arg(ap, char *);
	if (str == NULL)
		str = "(null)";
	ft_putstr_fd(str, 1);
	return (ft_strlen(str));
}

int	ft_put_ptr_to_str(va_list ap)
{
	char	*str;
	void	*ptr;
	int		length;

	ptr = va_arg(ap, void *);
	str = ptr_to_hex(ptr);
	if (str != NULL)
	{
		if (*str == '0' && ft_strlen(str) == 1)
		{
			free(str);
			str = "(nil)";
			ft_putstr_fd(str, 1);
			return (5);
		}
		else
		{
			length = ft_strlen(str);
			write(1, "0x", 2);
			ft_putstr_fd(str, 1);
			free(str);
			return (length + 2);
		}
	}
	return (0);
}

int	ft_putnumber(va_list ap)
{
	int		num;
	char	*str;
	int		length;

	str = NULL;
	num = va_arg(ap, int);
	str = ft_itoa(num);
	if (str != NULL)
	{
		length = ft_strlen(str);
		ft_putstr_fd(str, 1);
		free(str);
		return (length);
	}
	return (0);
}

int	ft_uint_to_str(va_list ap, char c)
{
	unsigned int	un_num;
	char			*str;
	int				length;

	str = NULL;
	if (c == 'u')
	{
		un_num = va_arg(ap, unsigned int);
		str = uitostr(un_num);
	}
	else if (c == 'x' || c == 'X')
	{
		un_num = va_arg(ap, unsigned int);
		str = uint_to_hex_uplow(un_num, c == 'x');
	}
	if (str != NULL)
	{
		length = ft_strlen(str);
		ft_putstr_fd(str, 1);
		free(str);
		return (length);
	}
	return (0);
}
