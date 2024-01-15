/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_free_bonus.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: splattje <splattje@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/27 09:02:45 by splattje      #+#    #+#                 */
/*   Updated: 2024/01/10 15:02:18 by splattje      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long_bonus.h"

void	free_lines(char **line)
{
	int	index;

	if (line != NULL)
	{
		index = -1;
		while (line[++index] != NULL)
			free(line[index]);
		free(line);
	}
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

void	free_texture(t_data *data, int index)
{
	printf("%d\n", index);
	while (index >= 0)
	{
		if (data->img[index] != NULL)
		{
			mlx_destroy_image(data->mlx, data->img[index]);
			free(data->img[index]);
		}
		index--;
	}
}

void	free_enemies(t_data *data)
{
	t_enemy	*tmp;

	if (data->enemies != NULL && *data->enemies != NULL)
	{
		while ((*data->enemies) != NULL)
		{
			tmp = (*data->enemies)->next;
			free(*data->enemies);
			*data->enemies = tmp;
		}
	}
}
