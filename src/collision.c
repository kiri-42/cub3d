#include "cub3d.h"

bool	has_wall(t_game_data *data, double x, double y)
{
	int	map_x;
	int	map_y;

	if (x < 0 || x > data->width || y < 0 || y > data->height)
		return (true);
	map_x = floor(x / TILE_SIZE);
	map_y = floor(y / TILE_SIZE);
	return (data->map[map_y][map_x] == MAP_WALL);
}

bool	has_wall_minimap(t_game_data *data, double x, double y)
{
	int	map_x;
	int	map_y;

	if (x < 0 || x > data->width || y < 0 || y > data->height)
		return (true);
	map_x = floor(x / MINIMAP_TILE_SIZE);
	map_y = floor(y / MINIMAP_TILE_SIZE);
	return (data->map[map_y][map_x] == MAP_WALL);
}
