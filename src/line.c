#include "cub3d.h"

int	to_chr_index(t_coord coord)
{
	return ((int)round(coord.y) * WIDTH + (int)round(coord.x));
}

t_coord	floor_coord(t_coord coord)
{
	coord.x = floor(coord.x);
	coord.y = floor(coord.y);
	return (coord);
}

void	get_delta(double *delta_x, double *delta_y)
{
	double	step;

	if (fabs(*delta_x) > fabs(*delta_y))
		step = fabs(*delta_x);
	else
		step = fabs(*delta_y);
	*delta_x /= step;
	*delta_y /= step;
}

void	draw_line(t_game_data *data, t_coord start, t_coord goal, int color)
{
	double	delta_x;
	double	delta_y;
	int		index;

	start = floor_coord(start);
	goal = floor_coord(goal);
	delta_x = goal.x - start.x;
	delta_y = goal.y - start.y;
	get_delta(&delta_x, &delta_y);
	while (fabs(goal.x - start.x) > 0.01 || fabs(goal.y - start.y) > 0.01)
	{
		index = to_chr_index(start);
		if (index >= 0 && index <= WIDTH * HEIGHT)
			map.addr[index] = color;
		start.x += delta_x;
		start.y += delta_y;
	}
	index = to_chr_index(start);
	if ((index >= 0 && index <= WIDTH * HEIGHT))
	{
		if (map.addr[index] == 0xFFFFFF)
			map.addr[index] = color;
	}
}

int	get_texture_color(int *imgd, double x, double y, double length)
{
	t_coord coord;
	int		index;

	length /= TILE_SIZE;
	x *= length;
	y *= length;
}

int	get_tex_color(t_game_data *data, t_fov *fov, int i)
{
	// size_t	i;
	int		tex_offset_x;
	int		tex_offset_y;
	int		distance_from_top;
	int		wall_top_pixel;
	int		wall_bottom_pixel;
	int		color;

	wall_top_pixel = ((HEIGHT) / 2) - (fov->wall_strip_height / 2);
	if (wall_top_pixel < 0)
		wall_top_pixel = 0;
	wall_bottom_pixel = (HEIGHT / 2) + (fov->wall_strip_height / 2);
	if (wall_bottom_pixel > HEIGHT)
		wall_bottom_pixel = HEIGHT;

	if (fov->was_hit_vert == true)
		tex_offset_x = (int)floor(fov->wall_hit.y) % TILE_SIZE;
	else
		tex_offset_x = (int)floor(fov->wall_hit.x) % TILE_SIZE;
	distance_from_top = i;
	tex_offset_y = distance_from_top * ((double)(TILE_SIZE) / fov->wall_strip_height);
	color = data->imgs.wall_north.addr[tex_offset_y * TILE_SIZE + tex_offset_x];
	return (color);
}

void	draw_straight_line(t_game_data *data, t_fov *fov, t_coord start, double length, t_part inte)
{
	double	delta_x;
	double	delta_y;
	int		index;
	int	color;
	size_t	i;

	i = 0;
	start = floor_coord(start);
	while (i < length)
	{
		index = to_chr_index(start);
		if (index >= 0 && index < WIDTH * HEIGHT)
		{
			// color = get_tex_color(data, fov, i);
			// color = get_texture_color(data->imgs.wall_north.addr, start.x, start.y, length);
			if (inte == CEILING)
				map.addr[index] = 0x0000FF;
			else if (inte == WALL)
				map.addr[index] = get_tex_color(data, fov, i);
			else if (inte == FLOOR)
				map.addr[index] = 0x0;
		}
		start.y++;
		i++;
	}
}
