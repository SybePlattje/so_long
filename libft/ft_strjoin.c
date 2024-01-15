/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: splattje <splattje@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/23 17:24:22 by splattje      #+#    #+#                 */
/*   Updated: 2023/12/28 10:06:51 by splattje      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char const *s2)
{
	char	*output;
	size_t	len;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	output = malloc(sizeof(char) * len);
	if (!output)
		return (NULL);
	ft_strlcpy(output, s1, len);
	free(s1);
	ft_strlcat(output, s2, len);
	return (output);
}
