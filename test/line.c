#include "debug.h"
#include <string.h>

void	draw_line(t_game_data *data, t_coord start, t_coord goal, int color)
{
	double	deltaX;
	double	deltaY;
	double	step;
	
	// printf("x:%f y:%f\n", goal.x, goal.y);
	// start.x = round(start.x);
	// start.y = round(start.y);
	// goal.x = round(goal.x);
	// goal.y = round(goal.y);
	start.x = floor(start.x);
	start.y = floor(start.y);
	goal.x = floor(goal.x);
	goal.y = floor(goal.y);
	deltaX = goal.x - start.x;
	deltaY = goal.y - start.y;
	// printf("xa:%f ya:%f\n", goal.x, goal.y);
	step = (fabs(deltaX) > fabs(deltaY)) ? fabs(deltaX) : fabs(deltaY);
	deltaX /= step;
	deltaY /= step;
	while (fabs(goal.x - start.x) > 0.01 || fabs(goal.y - start.y) > 0.01)
	{
		if (map.addr[TO_COORD(start.x, start.y)] == 0)
			break;
		map.addr[TO_COORD(start.x, start.y)] = color;
		start.x += deltaX;
		start.y += deltaY;
		if (map.addr[TO_COORD(start.x, start.y)] == 0xFFFFFF)
			map.addr[TO_COORD(start.x, start.y)] = color;
	}
	// printf("x:%f y:%f\n", start.x-deltaX, start.y-deltaY);
}
