NAME = cub3D
UNAME	=	$(shell uname)

DBGSRC	= $(wildcard ./src/*.c) #あとでわける
DBGOBJ	= $(DBGSRC:%.c=%.o)

CC = gcc
# CFLAGS = -Wall -Wextra -Werror -MMD -MP
CFLAGS = -MMD -MP
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

$(NAME) : $(DBGOBJ)
	make -C $(MLXDIR)
	make bonus -C ./libft
	$(CC) $(CFLAGS) $(DBGOBJ) $(INCLUDE) $(LFLAG) -o $(NAME)

all : $(NAME)

clean :
	make clean -C ./libft
	make clean -C $(MLXDIR)
	rm -rf $(DBGOBJ)

fclean : clean
	make fclean -C ./libft
	make clean -C $(MLXDIR)
	rm -rf $(NAME)
	rm -rf $(wildcard ./src/*.d)
	rm -rf $(wildcard ./src/*.o)

re : fclean all

.PHONY: all clean fclean re .c.o
