NAME := fdf
FLAGS := -Wall -Wextra -Werror
FILES := main.c
OBJ := $(FILES:.c=.o)
LIBFT := libft/
LIBFT_LIB := libft.a

all: do_libft $(NAME)

$(NAME): $(OBJ)
		cc $(FLAGS) $(OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz  -L$(LIBFT) -lft -o $@

%.o: %.c
		cc $(FLAGS) -I/usr/include -Imlx_linux -c $< -o $@

do_libft:
		make -C $(LIBFT)
		make bonus -C $(LIBFT)

clean:
		make clean -C $(LIBFT)
		rm -f $(OBJ) $(OBJ_S)

fclean: clean
		make fclean -C $(LIBFT)
		rm -f $(NAME) $(NAME_S)

re: fclean all
