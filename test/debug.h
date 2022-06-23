#ifndef  DEBUG_H
# define DEBUG_H

# include "cub3d.h"

# define ROWS 11
# define COLS 15
# define TILE_SIZE 32

# define WIDTH COLS * TILE_SIZE
# define HEIGHT ROWS * TILE_SIZE

# define LINE_RGB 0xFF0000

# define TO_COORD(X, Y) ((int)Y * WIDTH + (int)X)

typedef struct s_player_data
{
	int	x;
	int	y;
	void	*img;
	int	radius;
	int	turnDirection;	/* -1 if left, +1 if right */
	int	walkDirection;	/* -1 if back, +1 if front */
	float	rotationAngle;
	float	moveSpeed;
	float	rotationSpeed;
}	t_player_data;

int	*square;
void	*map;
t_player_data	player;

void	set_map(char ***m);
void	print_map_data(char **map);
void	dinit_map(t_game_data *data);
void	draw_white_square(t_game_data *data);
void	put_tile(t_game_data *data);
void	init_player();
void	draw_player(t_game_data *data);
void	dloop_start(t_game_data *data);

void	draw_line(int *addr, double x1, double y1, double x2, double y2);

void	draw_map(t_game_data *data);
void	set_line(double x1, double y1, double x2, double y2);


// p2.c
void	set_white_square();
void	draw_map2(t_game_data *data);
void	draw_all(t_game_data *data);
#endif