#include "debug.h"
#include <string.h>

void	draw_line(t_game_data *data, t_coord start, t_coord goal, int color)
{
	double	deltaX;
	double	deltaY;
	double	step;
	
	start.x = floor(start.x);
	start.y = floor(start.y);
	goal.x = floor(goal.x);
	goal.y = floor(goal.y);
	deltaX = goal.x - start.x;
	deltaY = goal.y - start.y;
	step = (fabs(deltaX) > fabs(deltaY)) ? fabs(deltaX) : fabs(deltaY);
	deltaX /= step;
	deltaY /= step;
	while (fabs(goal.x - start.x) > 0.01 || fabs(goal.y - start.y) > 0.01)
	{
		// printf("%f %f %f %f deltax:%f, deltay:%f\n", start.x, start.y, goal.x, goal.y, deltaX, deltaY);
		if (TO_COORD(start.x, start.y) >= 0 && TO_COORD(start.x, start.y) <= WIDTH * HEIGHT)
			map.addr[TO_COORD(start.x, start.y)] = color;
		start.x += deltaX;
		start.y += deltaY;
	}
	if ((TO_COORD(start.x, start.y) >= 0 && TO_COORD(start.x, start.y) <= WIDTH * HEIGHT))
	{
		if (map.addr[TO_COORD(start.x, start.y)] == 0xFFFFFF)
			map.addr[TO_COORD(start.x, start.y)] = color;
	}
}
