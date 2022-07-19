#include "cub3d.h"

bool	has_wall(char **map, double x, double y)
{
	int	map_x;
	int	map_y;

	if (x < 0 || x > WIDTH || y < 0 || y > HEIGHT)
		return (true);
	map_x = floor(x / TILE_SIZE);
	map_y = floor(y / TILE_SIZE);
	return (map[map_y][map_x] == '1');
}
