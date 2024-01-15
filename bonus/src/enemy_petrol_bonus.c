/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   enemy_petrol_bonus.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: splattje <splattje@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/08 15:49:48 by splattje      #+#    #+#                 */
/*   Updated: 2024/01/10 09:30:33 by splattje      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long_bonus.h"

static void	do_enemy_movement(t_data *data, t_enemy *enemy)
{
	if (enemy->enemy_dir == 'u')
		enemy->x--;
	if (enemy->enemy_dir == 'd')
		enemy->x++;
	if (has_enemy(data))
	{
		ft_printf("you died\n");
		on_destroy(data);
	}
	refresh_map(data, data->player_dir, 0);
}

static int	checks(t_data *data, int x, int y)
{
	if (data->map_file[x][y] == WALL)
		return (1);
	if (x == data->p_x && y == data->p_y)
	{
		ft_printf("you died\n");
		on_destroy(data);
	}
	return (0);
}

static int	check_enemy_movement(t_data *data, t_enemy *enemy)
{
	int		start_x;
	int		start_y;

	start_x = enemy->x;
	start_y = enemy->y;
	if (enemy->enemy_dir == 'u')
	{
		if (checks(data, start_x - 1, start_y))
		{
			enemy->enemy_dir = 'd';
			return (1);
		}
	}
	if (enemy->enemy_dir == 'd')
	{
		if (checks(data, start_x + 1, start_y))
		{
			enemy->enemy_dir = 'u';
			return (1);
		}
	}
	return (0);
}

int	enemy_petrol(t_data *data)
{
	t_enemy	*enemy;

	enemy = *data->enemies;
	while (enemy != NULL)
	{
		if (enemy->frames != 40000)
		{
			enemy->frames++;
		}
		else
		{
			enemy->frames = 0;
			if (check_enemy_movement(data, enemy))
				break ;
			do_enemy_movement(data, enemy);
		}
		enemy = enemy->next;
	}
	return (1);
}
