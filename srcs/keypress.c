/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   keypress.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: splattje <splattje@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/04 10:38:55 by splattje      #+#    #+#                 */
/*   Updated: 2024/01/10 14:57:00 by splattje      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	check_if_collect(t_data *data)
{
	t_collectible	*possiton;

	possiton = (*data->collectible);
	while (possiton != NULL)
	{
		if (possiton->x == data->p_x && possiton->y == data->p_y)
		{
			possiton->x = 0;
			possiton->y = 0;
			data->collected++;
			break ;
		}
		possiton = possiton->next;
	}
}

static void	refresh_map(t_data *data, char c)
{
	int	prev_x;
	int	prev_y;

	prev_x = data->p_x;
	prev_y = data->p_y;
	if (data->p_x == data->e_x
		&& data->p_y == data->e_y
		&& data->collected == data->max_collectibles)
		on_destroy(data);
	check_if_collect(data);
	if (c == 'u')
		prev_x++;
	if (c == 'd')
		prev_x--;
	if (c == 'l')
		prev_y++;
	if (c == 'r')
		prev_y--;
	if (prev_x == data->e_x && prev_y == data->e_y)
		data->map_file[prev_x][prev_y] = EXIT;
	else
		data->map_file[prev_x][prev_y] = OPEN_SPACE;
	data->map_file[data->p_x][data->p_y] = PLAYER;
	mlx_clear_window(data->mlx, data->win);
	set_img_to_window(*data);
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
	ft_putstr_fd("move counter: ", 1);
	ft_putnbr_fd(data->move_counter, 1);
	ft_putchar_fd('\n', 1);
	refresh_map(data, c);
}

static int	check_movement(t_data *data, char c)
{
	int	start_x;
	int	start_y;

	start_x = data->p_x;
	start_y = data->p_y;
	if (c == 'u')
		if (data->map_file[start_x - 1][start_y] != '1')
			return (1);
	if (c == 'd')
		if (data->map_file[start_x + 1][start_y] != '1')
			return (1);
	if (c == 'l')
		if (data->map_file[start_x][start_y - 1] != '1')
			return (1);
	if (c == 'r')
		if (data->map_file[start_x][start_y + 1] != '1')
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
