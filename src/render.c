#include "cub3d.h"

void	all_whitewash(t_game_data *data)
{
	size_t	i;

	i = 0;
	while (i < data->width * data->height)
		map.addr[i++] = 0x696969;
}

void	draw_minimap_ray(t_game_data *data)
{
	t_coord	start;
	t_coord	goal;
	size_t	i;

	i = 0;
	start.x = player.pos.x * MINIMAP_SCALE;
	start.y = player.pos.y * MINIMAP_SCALE;
	while (i < data->ray)
	{
		goal.x = data->fov[i].wall_hit.x * MINIMAP_SCALE;
		goal.y = data->fov[i].wall_hit.y * MINIMAP_SCALE;
		draw_line(data, start, goal, 0xFF0000);
		i++;
	}
}

void	render_all(t_game_data *data)
{
	all_whitewash(data);
	cast_all_rays(data);
	render_3d_projection_wall(data, data->fov);
	put_all_tile(data);
	draw_minimap_ray(data);
}
