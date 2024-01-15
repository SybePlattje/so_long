/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: splattje <splattje@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/06 15:19:07 by splattje      #+#    #+#                 */
/*   Updated: 2023/11/21 09:36:42 by splattje      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>

# include "./../libft.h"

int		ft_printf(const char *string, ...);
int		ft_data_sort(va_list ap, const char *string, int i);
char	*ptr_to_hex(void *ptr);
char	*uint_to_hex_uplow(unsigned int num, int uplow);
char	*uitostr(unsigned int num);
int		ft_putchar(va_list ap, char c, int inputplace);
int		ft_putstring(va_list ap);
int		ft_put_ptr_to_str(va_list ap);
int		ft_putnumber(va_list ap);
int		ft_uint_to_str(va_list ap, char c);

#endif