#include "cub3d.h"

void	all_whitewash(t_game_data *data)
{
	size_t	i;

	i = 0;
	while (i < WIDTH * HEIGHT)
		map.addr[i++] = 0x696969;
}

void	draw_minimap_ray(t_game_data *data)
{
	t_coord	start;
	t_coord	goal;
	size_t	i;

	i = 0;
	start.x = player.p_coord.x * MINIMAP_SCALE;
	start.y = player.p_coord.y * MINIMAP_SCALE;
	while (i < RAYS)
	{
		goal.x = data->fov[i].ray_goal.x;
		goal.y = data->fov[i].ray_goal.y;
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
