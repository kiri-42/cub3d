#include "cub3d.h"

void	put_all_tile(t_game_data *data)
{
	int	x;
	int	y;
	int	row;
	int	col;
	char	tile;

	row = (int)floor(MINIMAP_TILE_SIZE * data->rows);
	col = (int)floor(MINIMAP_TILE_SIZE * data->cols);

	y = 0;
	if ((size_t)row > data->win_height || (size_t)col > data->win_width)
	{
		free_all(data);
		exit(EXIT_FAILURE);
	}
	while (y < row)
	{
		x = 0;
		while (x < col)
		{
			tile = get_minimap_tile(data, x, y);
			if (tile == '1')
				data->map_img_data.addr[y * data->win_width + x] = 0x000000;
			else if (tile == '0' || tile == 'N')
				data->map_img_data.addr[y * data->win_width + x] = 0xFFFFFF;
			x++;
		}
		y++;
	}
}
