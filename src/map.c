#include "cub3d.h"

void	put_all_tile(t_game_data *data)
{
	int	x;
	int	y;
	int	row;
	int	col;

	row = (int)floor(MINIMAP_TILE_SIZE * data->rows);
	col = (int)floor(MINIMAP_TILE_SIZE * data->cols);

	y = 0;
	while (y < row)
	{
		x = 0;
		while (x < col)
		{
			if (has_wall_minimap(data, x, y) != true)
				data->map_img_data.addr[y * data->width + x] = 0xFFFFFF;
			else
				data->map_img_data.addr[y * data->width + x] = 0x000000;
			x++;
		}
		y++;
	}
}
