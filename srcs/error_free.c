/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_free.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: splattje <splattje@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/27 09:02:45 by splattje      #+#    #+#                 */
/*   Updated: 2024/01/04 09:33:17 by splattje      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	free_lines(char **line)
{
	int	index;

	index = -1;
	while (line[++index] != NULL)
		free(line[index]);
	free(line);
}

void	free_collectables(t_collectible **collectibles)
{
	t_collectible	*tmp;

	if (collectibles != NULL)
	{
		while (*collectibles != NULL)
		{
			tmp = (*collectibles)->next;
			free(*collectibles);
			*collectibles = tmp;
		}
	}
}

void	free_texture(t_data data, int index)
{
	while (index >= 0)
	{
		if (data.img[index] != NULL)
		{
			mlx_destroy_image(data.mlx, data.img[index]);
			free(data.img[index]);
		}
		index--;
	}
}
