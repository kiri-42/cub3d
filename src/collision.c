#include "cub3d.h"

bool	has_wall(t_game_data *data, double x, double y)
{
	int	map_x;
	int	map_y;

	if (x < 0 || x > data->map_width || y < 0 || y > data->map_height)
		return (true);
	map_x = floor(x / TILE_SIZE);
	map_y = floor(y / TILE_SIZE);
	if ((size_t)map_x > ft_strlen(data->map[map_y]))
		return (false);
	return (data->map[map_y][map_x] == MAP_WALL);
}

char	get_minimap_tile(t_game_data *data, double x, double y)
{
	int	map_x;
	int	map_y;

	if (x < 0 || x > data->map_width || y < 0 || y > data->map_height)
		return (' ');
	map_x = floor(x / MINIMAP_TILE_SIZE);
	map_y = floor(y / MINIMAP_TILE_SIZE);
	if ((size_t)map_x > ft_strlen(data->map[map_y]))
		return (' ');
	return (data->map[map_y][map_x]);
}
