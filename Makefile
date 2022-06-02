NAME = cub3D
UNAME	=	$(shell uname)

SRC =	main.c \
		check_arg.c \
		exit_error.c \
		read_cubfile.c
SRCDIR = ./src
SRCS	=	$(addprefix $(SRCDIR)/, $(SRC))
OBJS	=	$(SRCS:%.c=%.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIBFTDIR = ./libft
LIBFT = ft
MLXDIR	=	./minilibx
MLX = mlx
INCLUDE = -I./include -I$(LIBFTDIR) -I$(MLXDIR)

LFLAG = -L$(LIBFTDIR) -l$(LIBFT) -L$(MLXDIR) -l$(MLX)
ifeq ($(UNAME),Darwin)
	LFLAG += -L/usr/X11R6/lib -lX11 -lXext -framework OpenGL -framework AppKit
else
	LFLAG += -lXext -lX11 -lm
endif

.c.o :
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(NAME) : $(OBJS)
	make -C $(MLXDIR)
	make bonus -C ./libft
	$(CC) $(CFLAGS) $(OBJS) $(INCLUDE) $(LFLAG) -o $(NAME)

all : $(NAME)

clean :
	make clean -C ./libft
	make clean -C $(MLXDIR)
	rm -rf $(OBJS)

fclean : clean
	make fclean -C ./libft
	make clean -C $(MLXDIR)
	rm -rf $(NAME)

re : fclean all

.PHONY: all clean fclean re .c.o
