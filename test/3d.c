#include "debug.h"

int	color(int color, double distance)
{
	int	r;
	int	g;
	int	b;
	double	dark;

	r = color >> 16;
	g = color >> 8 & 0xFF;
	b = color & 0xFF;
	dark = (200 / distance);
	// if (distance > HEIGHT*2)
	// 	distance = HEIGHT*2;
	// r *= 1-distance/(HEIGHT*2);
	// g *= 1-distance/(HEIGHT*2);
	// b *= 1-distance/(HEIGHT*2);
	r *= dark;
	g *= dark;
	b *= dark;
	if (r > 0xFF)
		r = 0xFF;
	if (g > 0xFF)
		g = 0xFF;
	if (b > 0xFF)
		b = 0xFF;
	if (r < 0)
		r = 0;
	if (g < 0)
		g = 0;
	if (b < 0)
		b = 0;
	return (r << 16 | g << 8 | b);
}


void	render_3d_projection_wall(t_game_data *data, t_fov *fov)
{
	double	wall_strip_height;
	double	ray_distance;
	double	distance_projection_plane;
	t_coord	start;
	t_coord	goal;

	distance_projection_plane = (WIDTH / 2) / tan(FOV / 2);
	ray_distance = fov->distance * cos(fov->angle - player.rotationAngle);
	wall_strip_height = (TILE_SIZE / ray_distance) * distance_projection_plane;
	start.x = fov->id * WALL_STRIP_WIDTH;
	start.y = (HEIGHT / 2) - (wall_strip_height / 2);
	goal.x = start.x;
	goal.y = start.y + wall_strip_height;
	// color(0xFFFFFF, ray_distance);
	// draw_line(data, start, goal, 0xFFFFFF);
	draw_line(data, start, goal, color(0xFFFFFF, ray_distance));
	// exit(1);
	// print_fov_data(*fov);
}
