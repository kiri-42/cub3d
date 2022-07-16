#include "cub3d.h"

void	render_3d_projection_wall(t_game_data *data, t_fov *fov)
{
	double	ray_distance;
	double	distance_projection_plane;
	t_coord	start;
	size_t	i;

	i = 0;
	while (i < RAYS)
	{
		distance_projection_plane = (WIDTH / 2) / tan(FOV / 2);
		ray_distance = fov[i].distance * cos(fov[i].angle - player.rotation_angle);
		fov[i].wall_strip_height = (TILE_SIZE / ray_distance) * distance_projection_plane;

		start.x = fov[i].id * WALL_STRIP_WIDTH;
		start.y = 0;
		draw_straight_line(data, &fov[i], start, (HEIGHT / 2) - (fov[i].wall_strip_height / 2), CEILING);

		start.y = (HEIGHT / 2) - (fov[i].wall_strip_height / 2);
		draw_straight_line(data, &fov[i], start, fov[i].wall_strip_height, WALL);

		start.y += fov[i].wall_strip_height;
		if (start.y < HEIGHT)
			draw_straight_line(data, &fov[i], start, HEIGHT, FLOOR);
		i++;
	}
}
