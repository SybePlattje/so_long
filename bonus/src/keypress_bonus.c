/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   keypress_bonus.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: splattje <splattje@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/04 10:38:55 by splattje      #+#    #+#                 */
/*   Updated: 2024/01/09 17:31:46 by splattje      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long_bonus.h"

static void	check_if_collect(t_data *data)
{
	t_collectible	*possiton;

	possiton = (*data->collectible);
	while (possiton != NULL)
	{
		if (possiton->x == data->p_x && possiton->y == data->p_y)
		{
			data->collected++;
			possiton->x = 0;
			possiton->y = 0;
			break ;
		}
		possiton = possiton->next;
	}
}

void	refresh_map(t_data *data, char c, int flag)
{
	int	prev_x;
	int	prev_y;

	prev_x = data->p_x;
	prev_y = data->p_y;
	if (data->p_x == data->e_x
		&& data->p_y == data->e_y
		&& data->collected == data->max_collectibles)
	{
		ft_printf("victory\n");
		on_destroy(data);
	}
	check_if_collect(data);
	if (flag)
		movement_player(c, prev_x, prev_y, data);
	movement_enemy(data);
	mlx_clear_window(data->mlx, data->win);
	set_img_to_window(data);
}

static void	do_movement(t_data *data, char c)
{
	if (c == 'u')
		data->p_x--;
	if (c == 'd')
		data->p_x++;
	if (c == 'l')
		data->p_y--;
	if (c == 'r')
		data->p_y++;
	data->move_counter++;
	ft_printf("move counter %d\n", data->move_counter);
	data->player_dir = c;
	if (has_enemy(data))
	{
		ft_printf("you died\n");
		on_destroy(data);
	}
	refresh_map(data, c, 1);
}

static int	check_movement(t_data *data, char c)
{
	int	start_x;
	int	start_y;

	start_x = data->p_x;
	start_y = data->p_y;
	if (c == 'u')
		if (data->map_file[start_x - 1][start_y] != WALL)
			return (1);
	if (c == 'd')
		if (data->map_file[start_x + 1][start_y] != WALL)
			return (1);
	if (c == 'l')
		if (data->map_file[start_x][start_y - 1] != WALL)
			return (1);
	if (c == 'r')
		if (data->map_file[start_x][start_y + 1] != WALL)
			return (1);
	return (0);
}

void	handle_keypress(int keysym, t_data *data)
{
	if (keysym == 65307)
		on_destroy(data);
	if (keysym == 119 || keysym == 65362)
		if (check_movement(data, 'u'))
			do_movement(data, 'u');
	if (keysym == 115 || keysym == 65364)
		if (check_movement(data, 'd'))
			do_movement(data, 'd');
	if (keysym == 97 || keysym == 65361)
		if (check_movement(data, 'l'))
			do_movement(data, 'l');
	if (keysym == 100 || keysym == 65363)
		if (check_movement(data, 'r'))
			do_movement(data, 'r');
}
