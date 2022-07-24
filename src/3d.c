#include "cub3d.h"

void	render_3d_projection_wall(t_game_data *data, t_fov *fov)
{
	double	ray_distance;
	double	distance_projection_plane;
	t_coord	start;
	size_t	i;

	i = 0;
	while (i < data->ray)
	{
		distance_projection_plane = (data->win_width / 2) / tan(FOV / 2);
		ray_distance = fov[i].distance * cos(fov[i].angle \
		- data->player.rotation_angle);
		fov[i].wall_strip_height = (TILE_SIZE / ray_distance) \
		* distance_projection_plane;
		start.x = fov[i].id * WALL_STRIP_WIDTH;
		start.y = 0;
		draw_straight_line(data, &fov[i], start, (data->win_height / 2) \
		- (fov[i].wall_strip_height / 2), CEILING);
		start.y = (data->win_height / 2) - (fov[i].wall_strip_height / 2);
		draw_straight_line(data, &fov[i], start, \
		fov[i].wall_strip_height, WALL);
		start.y += fov[i].wall_strip_height;
		if (start.y < data->win_height)
			draw_straight_line(data, &fov[i], start, data->win_height, FLOOR);
		i++;
	}
}
