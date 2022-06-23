#include "debug.h"
#include <string.h>
#include <math.h>

void	draw_white_square(t_game_data *data)
{
	int	*addr;
	int		bits_per_pixel;
	int		line_lenght;
	int		endian;
	int	i;

	i = 0;
	square = mlx_new_image(data->mlx, TILE_SIZE, TILE_SIZE);
	addr = (int *)mlx_get_data_addr(square, &bits_per_pixel, &line_lenght, &endian);
	while (i < TILE_SIZE * TILE_SIZE)
	{
		addr[i] = 0xFFFFFF;
		if (i % TILE_SIZE == 0 || i < TILE_SIZE)
			addr[i] = 0x696969;
		i++;
	}
}

void	draw_player(t_game_data *data)
{
	int	*addr;
	int		bits_per_pixel;
	int		line_lenght;
	int		endian;
	int	i;

	i = 0;
	player.img = mlx_new_image(data->mlx, player.radius, player.radius);
	addr = (int *)mlx_get_data_addr(player.img, &bits_per_pixel, &line_lenght, &endian);
	while (i < player.radius * player.radius)
	{
		addr[i] = 0xFF0000;
		i++;
	}
}

void	init_player()
{
	player.x = WIDTH / 2;
	player.y = HEIGHT / 2;
	player.radius = 3;
	player.turnDirection = 0;	/* -1 if left, +1 if right */
	player.walkDirection = 0;	/* -1 if back, +1 if front */
	player.rotationAngle = M_PI / 2;
	player.moveSpeed = 2.0;
	player.rotationSpeed = 3 * (M_PI / 180);
}

void	put_tile(t_game_data *data)
{
	int i;
	int	j;
	 
	i = 0;
	while (i < ROWS)
	{
		j = 0;
		while (j < COLS)
		{
			if (data->map[i][j] != 1)
				mlx_put_image_to_window(data->mlx, data->win, square, j * TILE_SIZE, i * TILE_SIZE);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(data->mlx, data->win, player.img, player.x, player.y);
}

void	dinit_map(t_game_data *data)
{
	int win_x;
	int	win_y;

	data->mlx = mlx_init();
	if (!data->mlx)
		exit(EXIT_FAILURE);
	mlx_get_screen_size(data->mlx, &win_x, &win_y);
	if (0)
		exit(EXIT_FAILURE);
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, TITLE);
	if (!data->win)
		exit(EXIT_FAILURE);
	return ;
}

void	set_map(char ***m)
{
	char map[ROWS][COLS] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
	{1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	};

	int	i;
	int	j;

	i = 0;
	*m = malloc(sizeof(char *) * (ROWS + 1));
	while (i < ROWS)
	{
		j = 0;
		(*m)[i] = malloc(sizeof(char) * COLS);
		while (j < COLS)
		{
			(*m)[i][j] = map[i][j];
			j++;
		}
		i++;
	}
	(*m)[i] = NULL;
}