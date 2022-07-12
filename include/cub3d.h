#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <string.h>
# include <math.h>
# include <stdbool.h>
# include "libft.h"
# include "mlx.h"
# include <float.h>

# define TITLE "cub3D"

# define KEY_ESC 0xff1b
# define KEY_W 0x0077
# define KEY_A 0x0061
# define KEY_S 0x0073
# define KEY_D 0x0064

# define ROWS 11
# define COLS 15
# define TILE_SIZE 64
# define MINIMAP_SCALE 0.2
# define MINIMAP_TILE_SIZE (TILE_SIZE * MINIMAP_SCALE)

# define WIDTH COLS * TILE_SIZE
# define HEIGHT ROWS * TILE_SIZE
# define FOV (60 * (M_PI / 180))
# define WALL_STRIP_WIDTH 1
# define RAYS (WIDTH / WALL_STRIP_WIDTH)

# define LINE_RGB 0xFF0000

# define TO_COORD(X, Y) ((int)round(Y) * WIDTH + (int)round(X))

# ifndef M_PI
# define M_PI 3.14159265358979323846
# endif

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

typedef enum e_ud{
	UP = 1,
	DOWN = -1
}	t_ud;

typedef struct s_player_data
{
	t_coord	p_coord;
	void	*img;
	int		radius;
	int		turn_direction;	/* -1 if left, +1 if right */
	int		walk_direction;	/* -1 if back, +1 if front */
	double	rotation_angle;
	double	move_speed;
	double	rotation_speed;
}	t_player_data;

typedef struct s_img_data
{
	void	*img;
	int		*addr;
	int		bits_per_pixel;
	int		line_lenght;
	int		endian;
}	t_img_data;

t_img_data		map;
t_player_data	player;

void	check_arg(int ac, char **av);
void	init_game_data(t_game_data *gd);

//map.c
void	init_map(t_game_data *data);

//loop.c
void	loop_start(t_game_data *data);

//hook.c
int		close_window(void);
int		key_hook(int keycode, t_game_data *data);

void	dset_map(char ***m);
void	dinit_map(t_game_data *data);
void	dinit_player(void);
void	put_all_tile(t_game_data *data);
void	dloop_start(t_game_data *data);
void	draw_line(t_game_data *data, t_coord start, t_coord goal, int color);
bool	has_wall(char **map, double x, double y);
void	cast_all_rays(t_game_data *data);
void	render_3d_projection_wall(t_game_data *data, t_fov *fov);
void	render_all(t_game_data *data);

#endif
