/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_map_is_valid.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: splattje <splattje@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/14 09:58:23 by splattje      #+#    #+#                 */
/*   Updated: 2024/01/04 10:26:45 by splattje      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static char	*read_map_lines(int fd)
{
	char	*line;
	char	*all_lines;

	all_lines = ft_strdup("");
	if (!all_lines)
		return (perror("Error\nSomthing went wrong with memory"), NULL);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		all_lines = ft_strjoin(all_lines, line);
		if (!all_lines)
		{
			perror("Error\nMemory in strjoin");
			free(line);
			free(all_lines);
			return (NULL);
		}
		free(line);
	}
	free(line);
	return (all_lines);
}

static char	**validate_and_split(char *all_lines, t_data *data)
{
	char	**new_lines;
	int		index;

	if (all_lines[0] == '\0')
	{
		ft_putendl_fd("Error\nEmpty map", 2);
		free(all_lines);
		return (NULL);
	}
	index = 0;
	data->max_collectibles = 0;
	while (all_lines[index] != '\0')
	{
		if (all_lines[index] == 'C')
			data->max_collectibles++;
		if (all_lines[index++] == '\n' && all_lines[index] == '\n')
			return (free(all_lines),
				ft_putendl_fd("Error\nHole in map", 2), NULL);
	}
	new_lines = ft_split(all_lines, '\n');
	if (!new_lines)
		return (perror("Error\nMemory for new_line"), free(all_lines), NULL);
	if (set_collectibles(data, new_lines))
		return (ft_putendl_fd("Error\nSetting collectibles", 2), NULL);
	return (new_lines);
}

char	**map_to_2d_array(char *map_name, t_data *data)
{
	char	*all_lines;
	int		fd;
	char	**new_lines;
	int		height;
	int		width;

	all_lines = NULL;
	fd = open(map_name, O_RDONLY);
	if (fd < 0)
		return (perror("Error\nOpening the map"), NULL);
	all_lines = read_map_lines(fd);
	close(fd);
	if (all_lines == NULL)
		return (NULL);
	new_lines = validate_and_split(all_lines, data);
	if (new_lines == NULL)
		return (NULL);
	height = 0;
	while (new_lines[height] != NULL)
		height++;
	width = ft_strlen(new_lines[0]);
	data->height = (height * 32);
	data->width = (width * 32);
	free(all_lines);
	return (new_lines);
}

int	check_map_file(char *file_name)
{
	if (ft_strncmp((file_name + (ft_strlen(file_name) - 4)), ".ber", 4))
	{
		ft_putendl_fd("Error\nThe map is not a .ber file", 2);
		return (1);
	}
	return (0);
}

int	check_map_vallid(char *file_name, t_data *data)
{
	size_t			size;
	char			*full_file_path;

	if (check_map_file(file_name))
		return (1);
	full_file_path = ft_strdup("./maps/");
	full_file_path = ft_strjoin(full_file_path, file_name);
	if (full_file_path == NULL)
		return (perror("Error\nMemory"), 1);
	data->map_file = map_to_2d_array(full_file_path, data);
	free(full_file_path);
	if (data->map_file == NULL)
		return (1);
	size = 0;
	while (data->map_file[size] != NULL)
		size++;
	if (map_checks(data, size))
		return (1);
	return (0);
}
