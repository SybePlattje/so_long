/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   textures_bonus.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: splattje <splattje@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/02 16:17:49 by splattje      #+#    #+#                 */
/*   Updated: 2024/01/10 09:43:29 by splattje      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long_bonus.h"

static void	*set_xpm_to_img(t_data *data, char *file_name)
{
	void	*img;
	int		height;
	int		width;

	height = 32;
	width = 32;
	img = mlx_xpm_file_to_image(data->mlx, file_name, &width, &height);
	if (img == NULL)
		return (NULL);
	return (img);
}

static char	**set_file_names(void)
{
	char	**names;

	names = (char **)ft_calloc(sizeof(char *), 13);
	if (names == NULL)
		return (NULL);
	names[0] = "./bonus/textures/background.xpm";
	names[1] = "./bonus/textures/wall.xpm";
	names[2] = "./bonus/textures/exit_open.xpm";
	names[3] = "./bonus/textures/player_up.xpm";
	names[4] = "./bonus/textures/player_down.xpm";
	names[5] = "./bonus/textures/player_left.xpm";
	names[6] = "./bonus/textures/player_right.xpm";
	names[7] = "./bonus/textures/collectable.xpm";
	names[8] = "./bonus/textures/enemy_up.xpm";
	names[9] = "./bonus/textures/enemy_down.xpm";
	names[10] = "./bonus/textures/enemy_left.xpm";
	names[11] = "./bonus/textures/enemy_right.xpm";
	return (names);
}

int	set_textures(t_data *data)
{
	char	**file_names;
	int		index;

	file_names = set_file_names();
	if (file_names == NULL)
		return (1);
	index = 0;
	while (file_names[index])
	{
		data->img[index] = set_xpm_to_img(data, file_names[index]);
		if (data->img[index] == NULL)
		{
			if (index > 0)
				return (free_texture(data, index - 1), free(file_names),
					perror("Error\nMemory textures"), 1);
			else
				return (perror("Error\nMemory textures"), free(file_names), 1);
		}
		index++;
	}
	free(file_names);
	return (0);
}

void	mlx_to_window(t_data *data, char c, int x, int y)
{
	if (c == OPEN_SPACE)
		mlx_put_image_to_window(data->mlx, data->win,
			data->img[0], (x * 32), (y * 32));
	if (c == WALL)
		mlx_put_image_to_window(data->mlx, data->win,
			data->img[1], (x * 32), (y * 32));
	if (c == EXIT)
		mlx_put_image_to_window(data->mlx, data->win,
			data->img[2], (x * 32), (y * 32));
	if (c == PLAYER)
		set_player_texture(data, x, y, data->player_dir);
	if (c == COLLECTIBLE)
		mlx_put_image_to_window(data->mlx, data->win,
			data->img[7], (x * 32), (y * 32));
	if (c == ENEMY)
		set_enemy_texture(data, x, y);
}

int	set_img_to_window(t_data *data)
{
	int		i;
	int		ii;
	char	*m_counter;
	char	*count;

	i = -1;
	while (data->map_file[++i] != NULL)
	{
		ii = 0;
		while (data->map_file[i][ii] != '\0')
		{
			mlx_to_window(data, data->map_file[i][ii], ii, i);
			ii++;
		}
	}
	m_counter = ft_strdup("Move Counter: ");
	if (m_counter == NULL)
		return (1);
	count = NULL;
	count = ft_itoa(data->move_counter);
	if (count == NULL)
		return (free(m_counter), 1);
	m_counter = ft_strjoin(m_counter, count);
	mlx_string_put(data->mlx, data->win, 20, 20, 0xFFFFFF, m_counter);
	return (free(m_counter), free(count), 0);
}
