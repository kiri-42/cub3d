#include "debug.h"

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
	int	i;
	int	j;

	i = 0;
	while (i < ROWS)
	{
		j = 0;
		while (j < COLS)
		{
			if (data->map[i][j] != 1)
				paint_tile(i, j, 0xFFFFFF);
			else
				paint_tile(i, j, 0x000000);
			j++;
		}
		i++;
	}
}
