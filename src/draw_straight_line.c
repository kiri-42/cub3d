#include "cub3d.h"

void	draw_ceiling_straight_line(t_game_data *data,
		t_coord start, double length)
{
	size_t		index;
	size_t		i;
	t_img_data	*m;

	m = &data->map_img_data;
	i = 0;
	start = floor_coord(start);
	while (i < length)
	{
		index = to_chr_index(data->win_width, start, 1);
		if (index < data->win_width * data->win_height)
			m->addr[index] = data->ceiling_color.code;
		start.y++;
		i++;
	}
}

void	draw_wall_straight_line(t_game_data *data, t_fov *fov,
		t_coord start, double length)
{
	size_t		index;
	size_t		i;
	t_img_data	*m;

	m = &data->map_img_data;
	i = 0;
	start = floor_coord(start);
	while (i < length)
	{
		index = to_chr_index(data->win_width, start, 1);
		if (index < data->win_width * data->win_height)
			m->addr[index] = get_tex_color(data, fov, i);
		start.y++;
		i++;
	}
}

void	draw_floor_straight_line(t_game_data *data, t_coord start,
	double length)
{
	size_t		index;
	size_t		i;
	t_img_data	*m;

	m = &data->map_img_data;
	i = 0;
	start = floor_coord(start);
	while (i < length)
	{
		index = to_chr_index(data->win_width, start, 1);
		if (index < data->win_width * data->win_height)
			m->addr[index] = data->floor_color.code;
		start.y++;
		i++;
	}
}
