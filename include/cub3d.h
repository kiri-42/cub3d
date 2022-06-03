#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "libft.h"
# include "mlx.h"

# define PREFIX_SIZE 2

typedef struct s_texture_path
{
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
}	t_texture_path;

typedef struct s_rgb
{
	int	red;
	int	green;
	int	blue;
}	t_rgb;

typedef struct s_game_data
{
	t_texture_path	tp;
	t_rgb			floor_color;
	t_rgb			ceiling_color;
	char			**cubfile;
	size_t			cubfile_linage;
	char			**map;
}	t_game_data;

void	check_arg(int ac, char **av);
void	read_cubfile(t_game_data *gd, char *cubfile_name);
void	init_game_data(t_game_data *gd);
void	init_color(t_game_data *gd, char *line, char *prefix);
void	init_texture_path(t_game_data *gd, char *line, char *prefix);

// デバッグ用の関数
void	print_cubfile(t_game_data *gd);
void	print_texture_path(t_game_data *gd);
void	print_color(t_game_data *gd);
void	print_map(t_game_data *gd);

#endif
