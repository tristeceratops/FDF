SRCS := get_next_line.c
OBJS := $(SRCS:.c=.o)
CFLAGS := -Wall -Wextra -Werror
RM := rm -f
NAME := libgnl.a

all: $(NAME)

$(NAME): $(OBJS)
		ar rcs $(NAME) $(OBJS)
clean:
		$(RM) $(OBJS)
fclean: clean
		$(RM) $(NAME)
re: fclean all