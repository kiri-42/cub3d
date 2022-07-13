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
