#include "cub3d.h"

int	to_chr_index(int width, t_coord coord, double scale)
{
	return ((int)round(coord.y * scale) * width + (int)round(coord.x * scale));
}

t_cell	*get_cell_addr(t_game_data *gd, t_cell **map, t_coord coord)
{
	int	x;
	int	y;

	x = (int)floor((coord.x) / TILE_SIZE);
	y = (int)floor((coord.y) / TILE_SIZE);
	if ((size_t)x >= gd->cols || (size_t)y >= gd->rows)
		return (NULL);
	return (&map[y][x]);
}

static void	get_delta(double *delta_x, double *delta_y)
{
	double	step;

	if (fabs(*delta_x) > fabs(*delta_y))
		step = fabs(*delta_x);
	else
		step = fabs(*delta_y);
	*delta_x /= step;
	*delta_y /= step;
}

static bool	is_inside_blank(t_game_data *data, size_t index)
{
	if (!(index <= (data->map_width * data->map_height)))
		return (false);
	if (data->map_img_data.addr[index] == 0x0)
		return (false);
	return (true);
}

void	draw_line(t_game_data *data, t_coord start, t_coord goal, int color)
{
	double		delta_x;
	double		delta_y;
	size_t		index;
	t_img_data	*m;

	m = &data->map_img_data;
	start = floor_coord(start);
	goal = floor_coord(goal);
	delta_x = goal.x - start.x;
	delta_y = goal.y - start.y;
	get_delta(&delta_x, &delta_y);
	while (fabs(goal.x - start.x) > 0.01 || fabs(goal.y - start.y) > 0.01)
	{
		index = to_chr_index(data->win_width, start, 1);
		if (is_inside_blank(data, index))
			m->addr[index] = color;
		start.x += delta_x;
		start.y += delta_y;
	}
	index = to_chr_index(data->win_width, start, 1);
	if (is_inside_blank(data, index))
		m->addr[index] = color;
}

// void	draw_ceiling_straight_line(t_game_data *data,
// 		t_coord start, double length)
// {
// 	size_t		index;
// 	size_t		i;
// 	t_img_data	*m;

// 	m = &data->map_img_data;
// 	i = 0;
// 	start = floor_coord(start);
// 	while (i < length)
// 	{
// 		index = to_chr_index(data->win_width, start, 1);
// 		if (index < data->win_width * data->win_height)
// 			m->addr[index] = data->ceiling_color.code;
// 		start.y++;
// 		i++;
// 	}
// }

// void	draw_wall_straight_line(t_game_data *data, t_fov *fov,
// 		t_coord start, double length)
// {
// 	size_t		index;
// 	size_t		i;
// 	t_img_data	*m;

// 	m = &data->map_img_data;
// 	i = 0;
// 	start = floor_coord(start);
// 	while (i < length)
// 	{
// 		index = to_chr_index(data->win_width, start, 1);
// 		if (index < data->win_width * data->win_height)
// 			m->addr[index] = get_tex_color(data, fov, i);
// 		start.y++;
// 		i++;
// 	}
// }

// void	draw_floor_straight_line(t_game_data *data, t_coord start,
// 	double length)
// {
// 	size_t		index;
// 	size_t		i;
// 	t_img_data	*m;

// 	m = &data->map_img_data;
// 	i = 0;
// 	start = floor_coord(start);
// 	while (i < length)
// 	{
// 		index = to_chr_index(data->win_width, start, 1);
// 		if (index < data->win_width * data->win_height)
// 			m->addr[index] = data->floor_color.code;
// 		start.y++;
// 		i++;
// 	}
// }
