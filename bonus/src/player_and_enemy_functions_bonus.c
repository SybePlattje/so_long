/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player_and_enemy_functions_bonus.c                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: splattje <splattje@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/04 17:18:43 by splattje      #+#    #+#                 */
/*   Updated: 2024/01/10 15:02:37 by splattje      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long_bonus.h"

int	has_enemy(t_data *data)
{
	t_enemy	*enemy;

	enemy = *data->enemies;
	while (enemy != NULL)
	{
		if (data->p_x == enemy->x && data->p_y == enemy->y)
			return (1);
		enemy = enemy->next;
	}
	return (0);
}

void	movement_player(char c, int x, int y, t_data *data)
{
	if (c == 'u')
		x++;
	if (c == 'd')
		x--;
	if (c == 'l')
		y++;
	if (c == 'r')
		y--;
	if (x == data->e_x && y == data->e_y)
		data->map_file[x][y] = EXIT;
	else
		data->map_file[x][y] = OPEN_SPACE;
	data->map_file[data->p_x][data->p_y] = PLAYER;
}

void	movement_enemy(t_data *data)
{
	t_enemy	*enemy;
	int		prev_x;

	enemy = *data->enemies;
	while (enemy != NULL)
	{
		prev_x = enemy->x;
		if (enemy->enemy_dir == 'u')
			prev_x++;
		else
			prev_x--;
		data->map_file[enemy->x][enemy->y] = ENEMY;
		if (data->map_file[prev_x][enemy->y] == WALL)
			data->map_file[prev_x][enemy->y] = WALL;
		else if (data->map_file[prev_x][enemy->y] == PLAYER)
			data->map_file[prev_x][enemy->y] = PLAYER;
		else
			data->map_file[prev_x][enemy->y] = OPEN_SPACE;
		enemy = enemy->next;
	}
}

void	set_player_texture(t_data *data, int x, int y, char direction)
{
	if (direction == 'u')
		mlx_put_image_to_window(data->mlx, data->win,
			data->img[3], (x * 32), (y * 32));
	if (direction == 'd')
		mlx_put_image_to_window(data->mlx, data->win,
			data->img[4], (x * 32), (y * 32));
	if (direction == 'l')
		mlx_put_image_to_window(data->mlx, data->win,
			data->img[5], (x * 32), (y * 32));
	if (direction == 'r')
		mlx_put_image_to_window(data->mlx, data->win,
			data->img[6], (x * 32), (y * 32));
}

void	set_enemy_texture(t_data *data, int x, int y)
{
	t_enemy	*enemy;
	int		index;

	enemy = *data->enemies;
	index = 0;
	while (enemy != NULL)
	{
		if (enemy->enemy_dir == 'u')
			mlx_put_image_to_window(data->mlx, data->win,
				data->img[8], (x * 32), (y * 32));
		else if (enemy->enemy_dir == 'd')
			mlx_put_image_to_window(data->mlx, data->win,
				data->img[9], (x * 32), (y * 32));
		else if (enemy->enemy_dir == 'l')
			mlx_put_image_to_window(data->mlx, data->win,
				data->img[10], (x * 32), (y * 32));
		else if (enemy->enemy_dir == 'r')
			mlx_put_image_to_window(data->mlx, data->win,
				data->img[11], (x * 32), (y * 32));
		enemy = enemy->next;
		index++;
	}
}
