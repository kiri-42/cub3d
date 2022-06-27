#ifndef  DEBUG_H
# define DEBUG_H

# include "cub3d.h"

# define ROWS 11
# define COLS 15
# define TILE_SIZE 32

# define WIDTH COLS * TILE_SIZE
# define HEIGHT ROWS * TILE_SIZE
# define FOV (60 * (M_PI / 180))
# define WALL_STRIP_WIDTH 4
# define RAYS (WIDTH / WALL_STRIP_WIDTH)

# define LINE_RGB 0xFF0000

# define TO_COORD(X, Y) ((int)round(Y) * WIDTH + (int)round(X))

typedef enum e_ud{
	UP = 1,
	DOWN = -1	
}	t_ud;

typedef struct s_player_data
{
	double	x;
	double	y;
	void	*img;
	int	radius;
	int	turnDirection;	/* -1 if left, +1 if right */
	int	walkDirection;	/* -1 if back, +1 if front */
	double	rotationAngle;
	double	moveSpeed;
	double	rotationSpeed;
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

void	dset_map(char ***m);
void	dinit_map(t_game_data *data);
void	dinit_player(void);
void	put_all_tile(t_game_data *data);
void	dloop_start(t_game_data *data);
void	draw_line(t_img_data map, double x1, double y1, double x2, double y2);
bool	has_wall(char **map, double x, double y);
#endif