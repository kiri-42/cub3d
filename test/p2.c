#include "debug.h"
#include <string.h>
#include <math.h>

void	set_white_square()
{
	int	i;

	i = 0;
	square = malloc(sizeof(int) * (COLS * ROWS));
	while (i < TILE_SIZE * TILE_SIZE)
	{
		square[i] = 0xFFFFFF;
		if (i % TILE_SIZE == 0 || i < TILE_SIZE)
			square[i] = 0x696969;
		i++;
	}
}

void	put_tile_to_map(void *map, int i, int j, int color)
{
	int	k;
	int l;
	int		*addr;
	int		bits_per_pixel;
	int		line_lenght;
	int		endian;
	// (void)addr;
	// (void)i;
	// (void)j;

	addr = (int *)mlx_get_data_addr(map, &bits_per_pixel, &line_lenght, &endian);
	k = 0;

	while (k < TILE_SIZE)
	{
		l = 0;
		while (l < TILE_SIZE)
		{
			addr[((i * TILE_SIZE) + k) * WIDTH + ((j * TILE_SIZE) + l)] = color;
			if ((k % TILE_SIZE == 0 || l % TILE_SIZE == 0) && color != 0x000000)
				addr[((i * TILE_SIZE) + k) * WIDTH + ((j * TILE_SIZE) + l)] = 0x696969;
			l++;
		}
		k++;
	}
	return ;
}

void	draw_all(t_game_data *data)
{
	int		i;
	int		j;

	i = 0;
	while (i < ROWS)
	{
		j = 0;
		while (j < COLS)
		{
			if (data->map[i][j] != 1)
			{
				put_tile_to_map(map, i, j, 0xFFFFFF);
			}
			else
				put_tile_to_map(map, i, j, 0x000000);
			j++;
		}
		i++;
	}
}

void	draw_map2(t_game_data *data)
{
	map = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	
	draw_all(data);
	mlx_put_image_to_window(data->mlx, data->win, map, 0, 0);
	mlx_put_image_to_window(data->mlx, data->win, player.img, player.x, player.y);
}