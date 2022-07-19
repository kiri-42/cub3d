#include "cub3d.h"

void	draw_circle(t_game_data *data)
{
	int	*ptr;
	t_coord	coord;

	ptr = data->map_img_data.addr;
	coord.x = floor(data->player.pos.x - data->player.radius);
	coord.y = floor(data->player.pos.y - data->player.radius);
	while (coord.y < floor(data->player.pos.y + data->player.radius))
	{
		coord.x = floor(data->player.pos.x - data->player.radius);
		while (coord.x < floor(data->player.pos.x + data->player.radius))
		{
			if (coord.x > (int)data->win_width || coord.x < 0 || coord.y > (int)data->win_height || coord.y < 0)
				break ;
			if ((coord.x - data->player.pos.x) * (coord.x - data->player.pos.x) + (coord.y - data->player.pos.y) * (coord.y - data->player.pos.y) <= data->player.radius * data->player.radius)
				ptr[to_chr_index(data->win_width, coord, MINIMAP_SCALE)] = PLAYER_CIRCLE_COLOR;
			coord.x++;
		}
		coord.y++;
	}
}
