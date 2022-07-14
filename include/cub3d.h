#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <string.h>
# include <math.h>
# include <stdbool.h>
# include <float.h>
# include "libft.h"
# include "mlx.h"
# include <float.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>

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

# ifndef M_PI
# define M_PI 3.14159265358979323846
# endif

# define PREFIX_SIZE 2

typedef struct s_coord
{
	double	x;
	double	y;
}	t_coord;

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

typedef struct s_fov{
	int			id;
	double		angle;
	t_direction	d;
	double		distance;
	t_coord		ray_goal;
	bool		was_hit_vert;
}	t_fov;

typedef struct s_img_data
{
	void	*img;
	int		*addr;
	int		bits_per_pixel;
	int		line_lenght;
	int		endian;
}	t_img_data;

typedef struct s_imgs
{
	t_img_data	wall_north;
}	t_imgs;

typedef struct s_game_data
{
	t_texture_path	tp;
	t_rgb			floor_color;
	t_rgb			ceiling_color;
	int				cubfile_linage;
	char			**cubfile;
	char			**map;
	void			*mlx;
	void			*win;
	t_fov			*fov;
	t_imgs			imgs;
}	t_game_data;

typedef struct s_player_data
{
	t_coord	pos;
	void	*img;
	int		radius;
	int		turn_direction;	/* -1 if left, +1 if right */
	int		walk_direction;	/* -1 if back, +1 if front */
	double	rotation_angle;
	double	move_speed;
	double	rotation_speed;
}	t_player_data;

typedef struct s_can_read_color
{
	bool	floor;
	bool	ceiling;
}	t_can_read_color;

typedef struct s_can_read_texture
{
	bool	north;
	bool	south;
	bool	west;
	bool	east;
}	t_can_read_texture;

t_img_data		map;
t_player_data	player;

void	check_arg(int ac, char **av);
void	init_game_data(t_game_data *gd);
void	read_cubfile(t_game_data *gd, char *cubfile_name);
void	set_game_data(t_game_data *gd);
void	set_texture_path(t_game_data *gd, int *line_i);
void	set_color(t_game_data *gd, int *line_i);
bool	is_path_line(char *str);
bool	is_color_line(char *str);
void	free_cubfile(t_game_data *gd);
void	check_game_data(t_game_data *gd);
void	is_initialized_texture_path(t_texture_path tp);
void	is_initialized_rgb(t_rgb color);
void	is_initialized_map(char **map);
void	check_wall(t_game_data *gd);
void	is_invalid_rgb(t_rgb color);
void	is_open_texture_path(t_texture_path tp);


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

void	init_north_tex(t_game_data *data, t_imgs *img);

#endif
