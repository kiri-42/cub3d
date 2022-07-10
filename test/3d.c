#include "debug.h"

int	color(int color, double distance)
{
	int	r;
	int	g;
	int	b;
	int	ret;

	r = color & 0xFF;
	g = color & 0xFF00 >> 8;
	b = color >> 16;
	if (distance > HEIGHT*2)
		distance = HEIGHT*2;
	// printf("r:%d g:%d b:%d distance:%f, HEIGHT:%d\n", r, g, b, distance, HEIGHT);
	// printf("1-distance/(HEIGHT) : %f\n", 1-distance/(HEIGHT*2));
	// printf("r:%d g:%d b:%d\n", r, g, b);
	r *= 1-distance/(HEIGHT*2);
	g *= 1-distance/(HEIGHT*2);
	b *= 1-distance/(HEIGHT*2);
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
	// printf("r:%d g:%d b:%d\n", r, g, b);
	ret = r << 16;
	ret |= g << 8;
	ret |= b;

	// printf("%x\n", ret);
	// exit(1);
	return (ret);
}


void	render_3d_projection_wall(t_game_data *data, t_fov *fov)
{
	double	wall_strip_height;
	double	ray_distance;
	double	distance_projection_plane;
	t_coord	start;
	t_coord goal;

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
