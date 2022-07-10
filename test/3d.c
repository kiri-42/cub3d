#include "debug.h"

void	render_3d_projection_wall(t_game_data *data, t_fov *fov)
{
	double	wall_strip_height;
	double	ray_distance;
	double	distance_projection_plane;
	t_coord	start;
	t_coord goal;

	distance_projection_plane = (WIDTH / 2) / tan(FOV / 2);
	ray_distance = fov->distance;
	wall_strip_height = (TILE_SIZE / ray_distance) * distance_projection_plane;

	start.x = fov->id * WALL_STRIP_WIDTH;
	start.y = (HEIGHT / 2) - (wall_strip_height / 2);
	goal.x = start.x;
	goal.y = start.y + wall_strip_height;
	// printf("ray_distance : %f\n", ray_distance);
	// printf("distance_projection_plane : %f\n", distance_projection_plane);
	// printf("wall_strip_height : %f\n", wall_strip_height);
	// printf("i * WALL_STRIP_WIDTH : %f\n", fov->id * WALL_STRIP_WIDTH);
	// printf("(WINDOW_HEIGHT / 2) - (wallStripHeight / 2) : %f\n", (HEIGHT / 2) - (wall_strip_height / 2));
	draw_line(data, start, goal, 0xFFFF00);

	// exit(1);
	// print_fov_data(*fov);
}
