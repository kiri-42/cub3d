#include "cub3d.h"

int	color(t_fov *fov, int color, double distance)
{
	int	r;
	int	g;
	int	b;
	double	dark;

	r = color >> 16;
	g = color >> 8 & 0xFF;
	b = color & 0xFF;
	// dark = (200 / distance);
	dark = 1;
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
	if (fov->was_hit_vert == true)
	{
		r = 180;
		b = 180;
		g = 180;
	}
	else
	{
		r = 255;
		g = 255;
		b = 255;
	}
	return (r << 16 | g << 8 | b);
}

// int	color(int color, double distance)
// {
// 	int	r;
// 	int	g;
// 	int	b;
// 	double	dark;

// 	r = color >> 16;
// 	g = color >> 8 & 0xFF;
// 	b = color & 0xFF;
// 	dark = (200 / distance);
// 	r *= dark;
// 	g *= dark;
// 	b *= dark;

// 	if (r > 0xFF)
// 		r = 0xFF;
// 	if (g > 0xFF)
// 		g = 0xFF;
// 	if (b > 0xFF)
// 		b = 0xFF;
// 	if (r < 0)
// 		r = 0;
// 	if (g < 0)
// 		g = 0;
// 	if (b < 0)
// 		b = 0;
// 	return (r << 16 | g << 8 | b);
// }


void	render_3d_projection_wall(t_game_data *data, t_fov *fov)
{
	// double	wall_strip_height;
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
		// draw_straight_line(data, &fov[i], start, (HEIGHT / 2) - (fov[i].wall_strip_height / 2), CEILING);

		start.y = (HEIGHT / 2) - (fov[i].wall_strip_height / 2) + 1;
		draw_straight_line(data, &fov[i], start, fov[i].wall_strip_height, WALL);

		// start.y += fov[i].wall_strip_height + 1;
		// if (start.y < HEIGHT)
		// 	draw_straight_line(data, &fov[i], start, HEIGHT, FLOOR);
		i++;
	}
}
