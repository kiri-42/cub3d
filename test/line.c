#include "debug.h"
#include <string.h>

void	draw_line(t_game_data *data, t_coord start, t_coord goal, int color)
{
	double	delta_x;
	double	delta_y;
	double	step;

	start.x = floor(start.x);
	start.y = floor(start.y);
	goal.x = floor(goal.x);
	goal.y = floor(goal.y);
	delta_x = goal.x - start.x;
	delta_y = goal.y - start.y;
	step = (fabs(delta_x) > fabs(delta_y)) ? fabs(delta_x) : fabs(delta_y);
	delta_x /= step;
	delta_y /= step;
	while (fabs(goal.x - start.x) > 0.01 || fabs(goal.y - start.y) > 0.01)
	{
		// printf("%f %f %f %f deltax:%f, deltay:%f\n", start.x, start.y, goal.x, goal.y, delta_x, delta_y);
		if (TO_COORD(start.x, start.y) >= 0 && TO_COORD(start.x, start.y) <= WIDTH * HEIGHT)
			map.addr[TO_COORD(start.x, start.y)] = color;
		start.x += delta_x;
		start.y += delta_y;
	}
	if ((TO_COORD(start.x, start.y) >= 0 && TO_COORD(start.x, start.y) <= WIDTH * HEIGHT))
	{
		if (map.addr[TO_COORD(start.x, start.y)] == 0xFFFFFF)
			map.addr[TO_COORD(start.x, start.y)] = color;
	}
}
