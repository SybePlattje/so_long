/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_check_part_2_bonus.c                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: splattje <splattje@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/27 09:31:57 by splattje      #+#    #+#                 */
/*   Updated: 2024/01/10 14:47:00 by splattje      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long_bonus.h"

int	map_has_character(char **map, t_data *data)
{
	int	i;
	int	ii;
	int	character;

	i = 0;
	character = 0;
	while (map[i] != NULL)
	{
		ii = 0;
		while (map[i][ii] != '\0')
		{
			if (map[i][ii] == PLAYER)
			{
				character++;
				data->p_x = i;
				data->p_y = ii;
				data->player_dir = 'u';
			}
			ii++;
		}
		i++;
	}
	if (character != 1)
		return (ft_putendl_fd("Error\nMap doesn't have 1 player", 2), 1);
	return (0);
}

int	map_has_exit(char **map, t_data *data)
{
	int	i;
	int	ii;
	int	exit;

	i = 0;
	exit = 0;
	while (map[i] != NULL)
	{
		ii = 0;
		while (map[i][ii] != '\0')
		{
			if (map[i][ii] == EXIT)
			{
				exit++;
				data->e_x = i;
				data->e_y = ii;
			}
			ii++;
		}
		i++;
	}
	if (exit != 1)
		return (ft_putendl_fd("Error\nMap doesn't have 1 exit", 2), 1);
	return (0);
}

int	check_path(char **map, t_data *data)
{
	int	i;
	int	ii;
	int	max_c;

	i = data->p_x;
	ii = data->p_y;
	if (check_path_to_exit(map, data->p_x, data->p_y))
		return (ft_putendl_fd("Error\nNo path to exit", 2), 1);
	map_cleanup(map, data);
	max_c = data->max_collectibles;
	data->collected = 0;
	if (check_path_to_colectible(map, data->p_x, data->p_y, data))
		return (ft_putendl_fd("Error\nNo path to collectible", 2), 1);
	map_cleanup(map, data);
	return (0);
}

int	map_has_cha_col_exit(char **map, t_data *data)
{
	if (map_has_character(map, data))
		return (free_collectables(data->collectible),
			free(data->collectible), 1);
	if (map_has_exit(map, data))
		return (free_collectables(data->collectible),
			free(data->collectible), 1);
	if (map__has_enemy(map, data))
		return (free_collectables(data->collectible),
			free(data->collectible), 1);
	if (check_path(map, data))
		return (free_collectables(data->collectible),
			free(data->collectible), free_enemies(data),
			free(data->enemies), 1);
	data->collected = 0;
	return (0);
}

int	map_is_rectangle(char **map_file)
{
	int		index;
	size_t	size;

	index = 0;
	size = ft_strlen(map_file[0]);
	while (map_file[index] != NULL)
	{
		if (ft_strlen(map_file[index]) != size)
		{
			ft_putendl_fd("Error\nThe map is not a rectangle", 2);
			return (1);
		}
		index++;
	}
	return (0);
}
