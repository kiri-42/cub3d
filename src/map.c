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

// void	put_all_tile(t_game_data *data)
// {
// 	int		i;
// 	int		j;

// 	i = 0;
// 	while (i < ROWS)
// 	{
// 		j = 0;
// 		while (j < COLS)
// 		{
// 			if (data->map[i][j] != 1)
// 				paint_tile(i, j, 0xFFFFFF);
// 			else
// 				paint_tile(i, j, 0x000000);
// 			j++;
// 		}
// 		i++;
// 	}
// }

// void	has_wall_minimap(char **map, double x, double y)
// {
// 	int map_x;
// 	int	map_y;

// 	if (x < 0 || x > WIDTH || y < 0 || y > HEIGHT)
// 		return (true);
// 	map_x = floor(x / (int)floor(MINIMAP_TILE_SIZE));
// 	map_y = floor(y / (int)floor(MINIMAP_TILE_SIZE));

// 	return (map[map_y][map_x] == 1);
// }

bool	has_wall2(char **map, double x, double y)
{
	int	map_x;
	int	map_y;

	if (x < 0 || x > WIDTH || y < 0 || y > HEIGHT)
		return (true);
	map_x = floor(x / MINIMAP_TILE_SIZE);
	map_y = floor(y / MINIMAP_TILE_SIZE);
	// printf("x:%f y:%f\n", map_x, map_y);
	return (map[map_y][map_x] == 1);
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
			if (has_wall2(data->map, x, y) != 1)
				map.addr[y * WIDTH + x] = 0xFFFFFF;
			else
				map.addr[y * WIDTH + x] = 0x000000;
			x++;
		}
		y++;
	}
}
