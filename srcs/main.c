/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: splattje <splattje@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/11 15:12:30 by splattje      #+#    #+#                 */
/*   Updated: 2024/01/15 16:41:29 by splattje      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	on_destroy(t_data *data)
{
	int	index;

	free_lines(data->map_file);
	free_collectables(data->collectible);
	free(data->collectible);
	index = 4;
	while (index >= 0)
	{
		mlx_destroy_image(data->mlx, data->img[index]);
		index--;
	}
	free(data->img);
	mlx_destroy_window(data->mlx, data->win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(0);
	return (0);
}

int	on_keypress(int keysym, t_data *data)
{
	handle_keypress(keysym, data);
	return (0);
}

int	clean_up(t_data data)
{
	free_lines(data.map_file);
	if (data.collectible != NULL)
	{
		free_collectables(data.collectible);
		free(data.collectible);
	}
	if (data.img != NULL)
	{
		free_texture(data, 4);
		free(data.img);
	}
	if (data.win != NULL)
		mlx_destroy_window(data.mlx, data.win);
	if (data.mlx != NULL)
	{
		mlx_destroy_display(data.mlx);
		free(data.mlx);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_data			data;

	if (argc != 2)
		return (1);
	if (check_map_vallid(argv[1], &data))
		return (1);
	data.mlx = mlx_init();
	if (!data.mlx)
		return (clean_up(data));
	data.win = mlx_new_window(data.mlx, data.width, data.height, "so_long");
	if (!data.win)
		return (clean_up(data));
	data.img = ft_calloc(sizeof(void *), 6);
	if (data.img == NULL)
		return (clean_up(data));
	if (set_textures(data))
		return (clean_up(data));
	if (set_img_to_window(data))
		return (clean_up(data));
	data.move_counter = 0;
	data.collected = 0;
	mlx_hook(data.win, KeyPress, KeyPressMask, &on_keypress, &data);
	mlx_hook(data.win, DestroyNotify, StructureNotifyMask, &on_destroy, &data);
	mlx_loop(data.mlx);
	return (0);
}
