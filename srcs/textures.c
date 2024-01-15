/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   textures.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: splattje <splattje@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/02 16:17:49 by splattje      #+#    #+#                 */
/*   Updated: 2024/01/04 13:08:48 by splattje      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	*set_xpm_to_img(t_data data, char *file_name)
{
	void	*img;
	int		height;
	int		width;

	height = 32;
	width = 32;
	img = mlx_xpm_file_to_image(data.mlx, file_name, &width, &height);
	if (img == NULL)
		return (NULL);
	return (img);
}

static char	**set_file_names(void)
{
	char	**names;

	names = (char **)ft_calloc(sizeof(char *), 6);
	if (names == NULL)
		return (NULL);
	names[0] = "./textures/background.xpm";
	names[1] = "./textures/wall.xpm";
	names[2] = "./textures/exit_open.xpm";
	names[3] = "./textures/player_up.xpm";
	names[4] = "./textures/collectable.xpm";
	return (names);
}

int	set_textures(t_data data)
{
	char	**file_names;
	int		index;

	file_names = set_file_names();
	if (file_names == NULL)
		return (1);
	index = 0;
	while (file_names[index])
	{
		data.img[index] = set_xpm_to_img(data, file_names[index]);
		if (data.img[index] == NULL)
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

void	mlx_to_window(t_data data, char c, int x, int y)
{
	if (c == OPEN_SPACE)
		mlx_put_image_to_window(data.mlx, data.win,
			data.img[0], (x * 32), (y * 32));
	if (c == WALL)
		mlx_put_image_to_window(data.mlx, data.win,
			data.img[1], (x * 32), (y * 32));
	if (c == EXIT)
		mlx_put_image_to_window(data.mlx, data.win,
			data.img[2], (x * 32), (y * 32));
	if (c == PLAYER)
		mlx_put_image_to_window(data.mlx, data.win,
			data.img[3], (x * 32), (y * 32));
	if (c == COLLECTIBLE)
		mlx_put_image_to_window(data.mlx, data.win,
			data.img[4], (x * 32), (y * 32));
}

int	set_img_to_window(t_data data)
{
	int	i;
	int	ii;

	i = 0;
	while (data.map_file[i] != NULL)
	{
		ii = 0;
		while (data.map_file[i][ii] != '\0')
		{
			mlx_to_window(data, data.map_file[i][ii], ii, i);
			ii++;
		}
		i++;
	}
	return (0);
}
