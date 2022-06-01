UNAME	=	$(shell uname)

ifeq ($(UNAME),Darwin)

NAME = 		cub3D

SRC = main.c \
			check_arg.c \

SRCDIR = ./src

SRCS	=	$(addprefix $(SRCDIR)/, $(SRC))

OBJS = 		$(SRCS:.c=.o)

MLX_DIR = 	minilibx

MLX_LIB = 	minilibx/libmlx.a

FT_DIR = 	libft

FT_LIB = 	libft/libft.a

CC =		gcc

RM =		rm -f

CFLAGS =	-Wall -Wextra -Werror

INCLUDE = -I./include -I$(FT_DIR) -I$(MLX_DIR)

OPT = 		-L/usr/X11R6/lib -lX11 -lXext -framework OpenGL -framework AppKit

.PHONY: all re clean fclean

all:		$(NAME)

$(NAME):	$(OBJS) $(MLX_LIB) $(FT_LIB)
			$(CC) $^ $(INCLUDE) $(OPT) -o $@

$(MLX_LIB):
			make -C $(@D)

$(FT_LIB):
			make -C $(@D)

%.o:		%.c
			$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

re:
			make fclean
			make

clean:
			$(RM) $(OBJS)
			make -C $(FT_DIR) clean
			make -C $(MLX_DIR) clean

fclean:		clean
			$(RM) $(NAME)
			make -C $(FT_DIR) fclean

else

NAME = cub3D

SRC =	main.c \
			check_arg.c \
SRCDIR = ./src
SRCS	=	$(addprefix $(SRCDIR)/, $(SRC))
OBJS	=	$(SRCS:%.c=%.o)

CC = gcc
FLAGS = -Wall -Wextra -Werror
LIBFTDIR = ./libft
LIBFT = ft
MLXDIR	=	./minilibx
MLX = mlx
INCLUDE = -I./include -I$(LIBFTDIR) -I$(MLXDIR)

LFLAG = -L$(LIBFTDIR) -l$(LIBFT) -L$(MLXDIR) -l$(MLX) -lXext -lX11 -lm

.c.o :
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(NAME) : $(OBJS)
	make -C $(MLXDIR)
	make bonus -C ./libft
	$(CC) $(FLAGS) $(OBJS) $(INCLUDE) $(LFLAG) -o $(NAME)

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

endif
