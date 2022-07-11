#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <string.h>
# include <math.h>
# include <stdbool.h>
# include "libft.h"
# include "mlx.h"

# define TITLE "cub3D"

# define KEY_ESC 0xff1b
# define KEY_W 0x0077
# define KEY_A 0x0061
# define KEY_S 0x0073
# define KEY_D 0x0064

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

typedef struct s_direction{
	bool	up;
	bool	left;
	bool	down;
	bool	right;
}	t_direction;

typedef struct s_coord{
	double	x;
	double	y;
} t_coord;

typedef struct s_fov{
	int			id;
	double		angle;
	t_direction	d;
	double		distance;
	t_coord		ray_goal;
	bool		was_hit_vert;
}	t_fov;

typedef struct s_game_data
{
	t_texture_path	tp;
	t_rgb			floor_color;
	t_rgb			ceiling_color;
	char			**map;
	void			*mlx;
	void			*win;
	t_fov			*fov;
}	t_game_data;

void	check_arg(int ac, char **av);

//map.c
void	init_map(t_game_data *data);

//loop.c
void	loop_start(t_game_data *data);

//hook.c
int		close_window(void);
int		key_hook(int keycode, t_game_data *data);

#endif
