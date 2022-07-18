#include "cub3d.h"

int	to_chr_index(int width, t_coord coord)
{
	return ((int)round(coord.y) * width + (int)round(coord.x));
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

bool	is_inside_blank(t_game_data *data, size_t index)
{
	if (!(index <= (data->map_width * data->map_height)))
		return (false);
	if (data->map_img_data.addr[index] == 0x0)
		return (false);
	return (true);
}

void	draw_line(t_game_data *data, t_coord start, t_coord goal, int color)
{
	double	delta_x;
	double	delta_y;
	size_t	index;
	t_img_data	*m;

	m = &data->map_img_data;
	start = floor_coord(start);
	goal = floor_coord(goal);
	delta_x = goal.x - start.x;
	delta_y = goal.y - start.y;
	get_delta(&delta_x, &delta_y);
	while (fabs(goal.x - start.x) > 0.01 || fabs(goal.y - start.y) > 0.01)
	{
		index = to_chr_index(data->win_width, start);
		if (is_inside_blank(data, index))
			m->addr[index] = color;
		start.x += delta_x;
		start.y += delta_y;
	}
	index = to_chr_index(data->win_width, start);
	if (is_inside_blank(data, index))
		m->addr[index] = color;
}

int	darken_color(int color, double distance)
{
	int		r;
	int		g;
	int		b;
	double	dark;

	r = color >> 16;
	g = color >> 8 & 0xFF;
	b = color & 0xFF;
	dark = (200 / distance);
	if (dark > 1)
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
	return (r << 16 | g << 8 | b);
}

int	get_tex_color(t_game_data *data, t_fov *fov, int y)
{
	int		tex_offset_x;
	int		tex_offset_y;
	size_t	wall_bottom_pixel;
	int		color;

	wall_bottom_pixel = (data->win_height / 2) + (fov->wall_strip_height / 2);
	if (wall_bottom_pixel > data->win_height)
		wall_bottom_pixel = data->win_height;
	if (fov->was_hit_vert == true)
		tex_offset_x = (int)floor(fov->wall_hit.y) % TILE_SIZE;
	else
		tex_offset_x = (int)floor(fov->wall_hit.x) % TILE_SIZE;
	tex_offset_y = y * ((double)(TILE_SIZE) / fov->wall_strip_height);
	if (fov->d.up == true && fov->was_hit_vert == false)
		color = data->imgs.wall_north.addr[tex_offset_y * TILE_SIZE + tex_offset_x];
	else if (fov->d.right == true && fov->was_hit_vert == true)
		color = data->imgs.wall_east.addr[tex_offset_y * TILE_SIZE + tex_offset_x];
	else if (fov->d.left == true && fov->was_hit_vert == true)
		color = data->imgs.wall_west.addr[tex_offset_y * TILE_SIZE + (TILE_SIZE-1 - tex_offset_x)];
	else if (fov->d.down == true && fov->was_hit_vert == false)
		color = data->imgs.wall_south.addr[tex_offset_y * TILE_SIZE + (TILE_SIZE-1 - tex_offset_x)];
	else
		color = 0;
	color = darken_color(color, fov->distance);
	return (color);
}

void	draw_straight_line(t_game_data *data, t_fov *fov, t_coord start, double length, t_part part)
{
	size_t	index;
	size_t	i;
	t_img_data	*m;

	m = &data->map_img_data;
	i = 0;
	start = floor_coord(start);
	while (i < length)
	{
		index = to_chr_index(data->win_width, start);
		if (index < data->win_width * data->win_height)
		{
			if (part == CEILING)
				m->addr[index] = data->ceiling_color.code;
			else if (part == WALL)
				m->addr[index] = get_tex_color(data, fov, i);
			else if (part == FLOOR)
				m->addr[index] = data->floor_color.code;
		}
		start.y++;
		i++;
	}
}
