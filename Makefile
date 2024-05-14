NAME := fdf
FLAGS := -Wall -Wextra -Werror
FILES := main.c draw_line.c ft_error.c read_map.c isometric.c  draw_map.c my_pixel_put.c utils.c colors.c
OBJ := $(FILES:.c=.o)
LIBFT := libft/
LIBFT_A := $(LIBFT)libft.a
GNL := gnl/

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_A)
		cc $(FLAGS) $(OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz  -L$(LIBFT) -lft -L$(GNL) -lgnl -o $@

%.o: %.c
		cc $(FLAGS) -I/usr/include -Imlx_linux -c $< -o $@

$(LIBFT_A):
		make -C $(LIBFT)
		make -C $(GNL)
		make bonus -C $(LIBFT)

clean:
		make clean -C $(LIBFT)
		make clean -C $(GNL)
		rm -f $(OBJ) $(OBJ_S)

fclean: clean
		make fclean -C $(LIBFT)
		make fclean -C $(GNL)
		rm -f $(NAME) $(NAME_S)

re: fclean all
