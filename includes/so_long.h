/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: splattje <splattje@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/11 15:04:56 by splattje      #+#    #+#                 */
/*   Updated: 2024/01/04 12:15:40 by splattje      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "../libft/libft.h"
# include "../libft/get_next_line/get_next_line.h"
# include "../mlx/mlx.h"

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>
# include <X11/X.h>
# include <X11/keysym.h>

# define OPEN_SPACE '0'
# define WALL '1'
# define EXIT 'E'
# define COLLECTIBLE 'C'
# define PLAYER 'P'

typedef struct s_collectible
{
	int						x;
	int						y;
	struct s_collectible	*next;
}	t_collectible;

typedef struct s_data
{
	void			*mlx;
	void			*win;
	int				p_x;
	int				p_y;
	int				e_x;
	int				e_y;
	int				width;
	int				height;
	int				move_counter;
	int				collected;
	t_collectible	**collectible;
	int				max_collectibles;
	char			**map_file;
	void			**img;
}	t_data;
// main.c
int				on_destroy(t_data *data);
// error_free.c
void			free_lines(char **line);
void			free_collectables(t_collectible **collectibles);
void			free_texture(t_data data, int index);
// check_map_is_valid.c
char			**map_to_2d_array(char *map_name, t_data *data);
int				check_map_file(char *file_name);
int				check_map_vallid(char *file_name, t_data *data);
// map_check_part_2.c
int				map_has_character(char **map, t_data *data);
int				map_has_exit(char **map, t_data *data);
int				check_path(char **map, t_data *data);
int				map_has_cha_col_exit(char **map, t_data *data);
int				map_is_rectangle(char **file_name);
// map_check_part_3.c
int				map_wall_vallid(char **map_file, size_t size);
int				map_extra_characters(char **map);
int				map_checks(t_data *data, size_t size);
// collectible_utils.c
t_collectible	*new_collectible(int x, int y);
t_collectible	**add_back(t_collectible **head, int x, int y);
int				collectible_size(t_collectible **head);
int				set_collectibles(t_data *data, char **new_lines);
// path_checkers.c
int				check_path_to_exit(char **map, int row, int coll);
int				check_path_to_colectible(char **map, int row,
					int coll, int c_count);
void			map_cleanup(char **map, t_data *data);
// textures.c
int				set_textures(t_data data);
int				set_img_to_window(t_data data);
void			mlx_to_window(t_data data, char c, int x, int y);
// keypress.c
void			handle_keypress(int keysym, t_data *data);

#endif