NAME = libftprintf.a

SOURCES_MAND = ft_printf.c \
			ft_uint_to_hex_uplow.c \
			ft_ptr_to_hex.c \
			ft_uitostr.c \
			ft_output.c \

OBJS_MAND = $(SOURCES_MAND:.c=.o)

AR = ar

CC = cc
CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJS_MAND)
	$(AR) rcs $(NAME) $(OBJS_MAND)

clean:
	rm -f $(OBJS_MAND)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re