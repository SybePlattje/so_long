/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   path_checkers.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: splattje <splattje@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/27 11:45:16 by splattje      #+#    #+#                 */
/*   Updated: 2024/01/04 15:31:33 by splattje      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	check_path_to_exit(char **map, int row, int coll)
{
	int	row_max;
	int	coll_max;

	coll_max = ft_strlen(map[0]);
	row_max = 0;
	while (map[row_max] != NULL)
		row_max++;
	if (row < 0 || row >= row_max || coll < 0 || coll >= coll_max)
		return (1);
	if (map[row][coll] == EXIT)
		return (0);
	if (map[row][coll] == WALL || map[row][coll] == 'V')
		return (1);
	map[row][coll] = 'V';
	if (!check_path_to_exit(map, row, (coll + 1)))
		return (0);
	if (!check_path_to_exit(map, row, (coll - 1)))
		return (0);
	if (!check_path_to_exit(map, (row + 1), coll))
		return (0);
	if (!check_path_to_exit(map, (row - 1), coll))
		return (0);
	return (1);
}

int	check_path_to_colectible(char **map, int row, int coll, int c_count)
{
	int	row_max;
	int	coll_max;

	coll_max = ft_strlen(map[0]);
	row_max = 0;
	while (map[row_max] != NULL)
		row_max++;
	if (row < 0 || row >= row_max || coll < 0 || coll >= coll_max)
		return (1);
	if (c_count == 0)
		return (0);
	if (map[row][coll] == WALL || map[row][coll] == 'V')
		return (1);
	if (map[row][coll] == COLLECTIBLE)
		c_count--;
	map[row][coll] = 'V';
	if (!check_path_to_colectible(map, row, (coll + 1), c_count))
		return (0);
	if (!check_path_to_colectible(map, row, (coll - 1), c_count))
		return (0);
	if (!check_path_to_colectible(map, (row + 1), coll, c_count))
		return (0);
	if (!check_path_to_colectible(map, (row - 1), coll, c_count))
		return (0);
	return (1);
}

void	map_cleanup(char **map, t_data *data)
{
	int				i;
	int				ii;
	t_collectible	*tmp;

	i = -1;
	while (map[++i] != NULL)
	{
		ii = -1;
		while (map[i][++ii] != '\0')
		{
			if (map[i][ii] == 'V')
				map[i][ii] = '0';
		}
	}
	tmp = *data->collectible;
	while (tmp != NULL)
	{
		map[tmp->x][tmp->y] = 'C';
		tmp = tmp->next;
	}
	map[data->p_x][data->p_y] = 'P';
	map[data->e_x][data->e_y] = 'E';
	i = -1;
}
