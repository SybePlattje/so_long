/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   so_long_bonus.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: splattje <splattje@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/04 15:57:19 by splattje      #+#    #+#                 */
/*   Updated: 2024/01/10 13:46:25 by splattje      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H

# include "../../libft/libft.h"
# include "../../libft/ft_printf/ft_printf.h"
# include "../../libft/get_next_line/get_next_line.h"
# include "../../mlx/mlx.h"

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
# define ENEMY 'A'

typedef struct s_collectible
{
	int						x;
	int						y;
	struct s_collectible	*next;
}	t_collectible;

typedef struct s_enemy
{
	int				x;
	int				y;
	char			enemy_dir;
	int				frames;
	struct s_enemy	*next;
}	t_enemy;

typedef struct s_data
{
	void			*mlx;
	void			*win;
	int				p_x;
	int				p_y;
	char			player_dir;
	int				e_x;
	int				e_y;
	int				width;
	int				height;
	int				move_counter;
	int				collected;
	t_collectible	**collectible;
	t_enemy			**enemies;
	int				max_collectibles;
	int				max_enemies;
	char			**map_file;
	void			**img;
}	t_data;
// main_bonus.c
int				on_destroy(t_data *data);
int				clean_up(t_data *data);
// error_free_bonus.c
void			free_lines(char **line);
void			free_collectables(t_collectible **collectibles);
void			free_texture(t_data *data, int index);
void			free_enemies(t_data *data);
// check_map_is_valid_bonus.c
char			**map_to_2d_array(char *map_name, t_data *data);
int				check_map_file(char *file_name);
int				check_map_vallid(char *file_name, t_data *data);
// map_check_part_2_bonus.c
int				map_has_character(char **map, t_data *data);
int				map_has_exit(char **map, t_data *data);
int				check_path(char **map, t_data *data);
int				map_has_cha_col_exit(char **map, t_data *data);
int				map_is_rectangle(char **file_name);
// map_check_part_3_bonus.c
int				map_wall_vallid(char **map_file, size_t size);
int				map_extra_characters(char **map);
int				map_checks(t_data *data, size_t size);
int				map__has_enemy(char **map, t_data *data);
// collectible_utils_bonus.c
t_collectible	*new_collectible(int x, int y);
t_collectible	**add_back(t_collectible **head, int x, int y);
int				collectible_size(t_collectible **head);
int				set_collectibles(t_data *data, char **new_lines);
// path_checkers_bonus.c
int				check_path_to_exit(char **map, int row, int coll);
int				check_path_to_colectible(char **map, int row,
					int coll, t_data *data);
void			map_cleanup(char **map, t_data *data);
// textures_bonus.c
int				set_textures(t_data *data);
int				set_img_to_window(t_data *data);
void			mlx_to_window(t_data *data, char c, int x, int y);
// keypress_bonus.c
void			handle_keypress(int keysym, t_data *data);
void			refresh_map(t_data *data, char c, int flag);
// player_and_enemy_functions_bonus.c
void			set_player_texture(t_data *data, int x, int y, char direction);
void			set_enemy_texture(t_data *data, int x, int y);
void			movement_player(char c, int x, int y, t_data *data);
void			movement_enemy(t_data *data);
int				has_enemy(t_data *data);
// enemy_utils_bonus
t_enemy			*new_enemy(int x, int y, char direction);
t_enemy			*last_enemy(t_enemy	*enemy);
t_enemy			**add_enemy_to_back(int x, int y, t_data *data);
// enemy_petrol_bonus.c
int				enemy_petrol(t_data *data);

#endif