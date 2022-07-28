NAME = cub3D
UNAME	=	$(shell uname)

SRCS	= ./src/map.c \
		./src/collision.c \
		./src/check_wall.c \
		./src/rays_utils1.c \
		./src/rays_utils2.c \
		./src/line_utils.c \
		./src/line.c \
		./src/init.c \
		./src/is_open.c \
		./src/color.c \
		./src/coord.c \
		./src/rays.c \
		./src/free.c \
		./src/key_hook.c \
		./src/set_color.c \
		./src/main.c \
		./src/3d.c \
		./src/loop.c \
		./src/dupmap.c \
		./src/check_game_data.c \
		./src/set_texture_path.c \
		./src/set_game_data_utils.c \
		./src/set_game_data.c \
		./src/init_game_data.c \
		./src/render.c \
		./src/read_cubfile.c \
		./src/circle.c \
		./src/free_cubfile.c \
		./src/is_initialized.c \
		./src/is_invalid.c \
		./src/check_arg.c \
		./src/move.c \
		./src/open_tex.c

SRCSB	= ./src/map.c \
		./src/collision.c \
		./src/check_wall_bonus.c \
		./src/rays_utils1.c \
		./src/rays_utils2.c \
		./src/line_utils.c \
		./src/line.c \
		./src/init.c \
		./src/is_open.c \
		./src/color.c \
		./src/coord.c \
		./src/rays.c \
		./src/free.c \
		./src/key_hook.c \
		./src/set_color.c \
		./src/main.c \
		./src/3d.c \
		./src/loop.c \
		./src/dupmap.c \
		./src/check_game_data.c \
		./src/set_texture_path.c \
		./src/set_game_data_utils.c \
		./src/set_game_data.c \
		./src/init_game_data.c \
		./src/render.c \
		./src/read_cubfile.c \
		./src/circle.c \
		./src/free_cubfile.c \
		./src/is_initialized.c \
		./src/is_invalid.c \
		./src/check_arg.c \
		./src/move.c \
		./src/open_tex.c

OBJS	= $(SRCS:%.c=%.o)
OBJSB	= $(SRCSB:%.c=%.o)

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
	rm -rf $(OBJS) $(OBJSB)

fclean : clean
	make fclean -C ./libft
	make clean -C $(MLXDIR)
	rm -rf $(NAME)
	rm -rf $(OBJS) $(OBJSB)

re : fclean all

bonus : $(OBJSB)
	make -C $(MLXDIR)
	make bonus -C ./libft
	$(CC) $(CFLAGS) $(OBJSB) $(INCLUDE) $(LFLAG) -o $(NAME)

.PHONY: all clean fclean re .c.o
