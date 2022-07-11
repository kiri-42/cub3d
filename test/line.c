#include "debug.h"
#include <string.h>

void	draw_line(t_img_data map, t_coord start, t_coord goal)
{
	double	deltaX;
	double	deltaY;
	double	step;

	start.x = round(start.x);
	start.y = round(start.y);
	goal.x = round(goal.x);
	goal.y = round(goal.y);
	deltaX = goal.x - start.x;
	deltaY = goal.y - start.y;
	step = (fabs(deltaX) > fabs(deltaY)) ? fabs(deltaX) : fabs(deltaY);
	deltaX /= step;
	deltaY /= step;
	while (fabs(goal.x - start.x) > 0.01 || fabs(goal.y - start.y) > 0.01)
	{
		map.addr[TO_COORD(start.x, start.y)] = 0xb3b3b3;
		start.x += deltaX;
		start.y += deltaY;
	}
}
