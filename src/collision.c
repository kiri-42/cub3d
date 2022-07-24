#include "cub3d.h"

bool	has_wall(t_game_data *data, double x, double y, char ob)
{
	size_t	map_x;
	size_t	map_y;

	if (x < 0 || x > data->map_width || y < 0 || y > data->map_height)
		return (true);
	map_x = floor(x / TILE_SIZE);
	map_y = floor(y / TILE_SIZE);
	if (map_x >= data->cols || map_y >= data->rows)
		return (false);
	if (ob == MAP_WALL && data->map2[map_y][map_x].type == MAP_WALL)
		return (true);
	return (data->map2[map_y][map_x].type == ob);
}

char	get_minimap_tile(t_game_data *data, double x, double y)
{
	size_t	map_x;
	size_t	map_y;

	if (x < 0 || x > data->map_width || y < 0 || y > data->map_height)
		return (' ');
	map_x = floor(x / MINIMAP_TILE_SIZE);
	map_y = floor(y / MINIMAP_TILE_SIZE);
	if (map_x >= data->cols || map_y >= data->rows)
		return (' ');
	return (data->map2[map_y][map_x].type);
}
