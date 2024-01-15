/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_check_part_3.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: splattje <splattje@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/02 15:24:00 by splattje      #+#    #+#                 */
/*   Updated: 2024/01/04 11:27:46 by splattje      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	map_wall_vallid(char **map_file, size_t size)
{
	size_t	i;
	size_t	ii;
	int		flag;

	i = 0;
	flag = 0;
	while (flag == 0 && map_file[i] != NULL)
	{
		if (i == 0 || i == size - 1)
		{
			ii = 0;
			while (flag == 0 && map_file[i][ii] != '\0')
			{
				if (map_file[i][ii++] != WALL)
					flag = 1;
			}
		}
		else if (map_file[i][0] != WALL &&
			map_file[i][ft_strlen(map_file[i])] != WALL)
			flag = 1;
		i++;
	}
	if (flag == 1)
		ft_putendl_fd("Error\nMap not surrounded by walls", 2);
	return (flag);
}

int	map_extra_characters(char **map)
{
	int	i;
	int	ii;

	i = 0;
	while (map[i] != NULL)
	{
		ii = 0;
		while (map[i][ii] != '\0')
		{
			if (map[i][ii] != WALL && map[i][ii] != OPEN_SPACE
				&& map[i][ii] != EXIT && map[i][ii] != PLAYER
				&& map[i][ii] != COLLECTIBLE)
				return (ft_putendl_fd("Error\nUnknown character", 2), 1);
			ii++;
		}
		i++;
	}
	return (0);
}

int	map_checks(t_data *data, size_t size)
{
	if (map_is_rectangle(data->map_file))
		return (free_lines(data->map_file),
			free_collectables(data->collectible),
			free(data->collectible), 1);
	if (map_wall_vallid(data->map_file, size))
		return (free_lines(data->map_file),
			free_collectables(data->collectible),
			free(data->collectible), 1);
	if (map_extra_characters(data->map_file))
		return (free_lines(data->map_file),
			free_collectables(data->collectible),
			free(data->collectible), 1);
	if (data->max_collectibles == 0)
		return (free_lines(data->map_file), free(data->collectible),
			ft_putendl_fd("Error\nNo collectibles", 2), 1);
	if (data->collectible == NULL)
		return (free_lines(data->map_file), 1);
	if (map_has_cha_col_exit(data->map_file, data))
		return (free_lines(data->map_file), 1);
	return (0);
}
