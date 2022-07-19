#include "cub3d.h"

void	paint_tile(int i, int j, int color)
{
	int	k;
	int	l;
	int	coord;

	k = 0;
	while (k < TILE_SIZE)
	{
		l = 0;
		while (l < TILE_SIZE)
		{
			coord = ((i * TILE_SIZE) + k) * WIDTH + ((j * TILE_SIZE) + l);
			map.addr[coord] = color;
			if ((k % TILE_SIZE == 0 || l % TILE_SIZE == 0) && color != 0x000000)
				map.addr[coord] = 0x696969;
			l++;
		}
		k++;
	}
	return ;
}

void	put_all_tile(t_game_data *data)
{
	int	x;
	int	y;
	int	row;
	int	col;

	row = (int)floor(MINIMAP_TILE_SIZE * ROWS);
	col = (int)floor(MINIMAP_TILE_SIZE * COLS);

	y = 0;
	while (y < row)
	{
		x = 0;
		while (x < col)
		{
			if (has_wall(data->map, x, y))
				map.addr[y * WIDTH + x] = 0x000000;
			else
				map.addr[y * WIDTH + x] = 0xFFFFFF;
			// printf("%d\n", map.addr[y * WIDTH + x]);
			x++;
		}
		y++;
	}
}
