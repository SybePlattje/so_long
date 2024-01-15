NAME = so_long
BONUS_NAME = so_long_bonus
MINILIBX_DIR = ./mlx
MINILIBX = $(MINILIBX_DIR)/libmlx.a
SRC_DIR = ./srcs
BONUS_SRC_DIR = ./bonus/src
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

SOURCES = $(SRC_DIR)/check_map_is_valid.c \
		$(SRC_DIR)/collectible_utils.c \
		$(SRC_DIR)/error_free.c \
		$(SRC_DIR)/main.c \
		$(SRC_DIR)/map_check_part_2.c \
		$(SRC_DIR)/map_check_part_3.c \
		$(SRC_DIR)/path_checkers.c \
		$(SRC_DIR)/textures.c \
		$(SRC_DIR)/keypress.c \

BONUS_SRCS = $(BONUS_SRC_DIR)/check_map_is_valid_bonus.c \
			$(BONUS_SRC_DIR)/collectible_utils_bonus.c \
			$(BONUS_SRC_DIR)/enemy_petrol_bonus.c \
			$(BONUS_SRC_DIR)/enemy_utils_bonus.c \
			$(BONUS_SRC_DIR)/error_free_bonus.c \
			$(BONUS_SRC_DIR)/main_bonus.c \
			$(BONUS_SRC_DIR)/map_check_part_2_bonus.c \
			$(BONUS_SRC_DIR)/map_check_part_3_bonus.c \
			$(BONUS_SRC_DIR)/path_checkers_bonus.c \
			$(BONUS_SRC_DIR)/player_and_enemy_functions_bonus.c \
			$(BONUS_SRC_DIR)/textures_bonus.c \
			$(BONUS_SRC_DIR)/keypress_bonus.c \

OBJS = $(SOURCES:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Werror -Wextra -g
MLXFLAGS = -L ./mlx -lmlx -Ilmlx -lXext -lX11

$(NAME): $(OBJS)
	@make -C $(LIBFT_DIR)
	@make -C $(LIBFT_DIR) gnl
	@make -C $(MINILIBX_DIR)
	@$(CC) $(CFLAGS) $(OBJS) $(MLXFLAGS) -L $(LIBFT_DIR) -l:libft.a -o $(NAME)

all: $(NAME)

bonus: $(BONUS_OBJS)
	@make -C $(LIBFT_DIR)
	@make -C $(LIBFT_DIR) printf
	@make -C $(LIBFT_DIR) gnl
	@make -C $(MINILIBX_DIR)
	@$(CC) $(CFLAGS) $(BONUS_OBJS) $(MLXFLAGS) -L $(LIBFT_DIR) -l:libft.a -o $(BONUS_NAME)

clean:
	@rm -rf $(OBJS) $(BONUS_OBJS)

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(BONUS_NAME)

re: fclean all

bonus_re: fclean bonus

.PHONY: all bonus clean fclean re bonus_re