#include "debug.h"
#include <string.h>

// void	draw_line(t_img_data *map, double x1, double y1, double x2, double y2)
// {
// 	double	deltaX;
// 	double	deltaY;
// 	double	step;

// 	printf("%f %f %f %f\n", x1, y1, x2, y2);
// 	if (x1 > WIDTH|| y1 > HEIGHT|| x2 > WIDTH || y2 > HEIGHT)
// 	{
// 		printf("out of map\n");
// 		exit(EXIT_FAILURE);
// 	}
// 	deltaX = x2 - x1;
// 	deltaY = y2 - y1;
// 	step = (fabs(deltaX) > fabs(deltaY)) ? fabs(deltaX) : fabs(deltaY);
// 	deltaX /= step;
// 	deltaY /= step;
// 	while (fabs(x2 - x1) > 0.01 || fabs(y2 - y1) > 0.01)
// 	{
// 		printf("%f %f\n", fabs(x2 - x1), fabs(y2 - y1));
// 		if (TO_COORD(x1, y1) >= WIDTH * HEIGHT || TO_COORD(x1, y1) <= 0)
// 			break;
// 		map->addr[TO_COORD(x1, y1)] = LINE_RGB;
// 		x1 += deltaX;
// 		y1 += deltaY;
// 	}
// }

void	draw_line(t_img_data map, double x1, double y1, double x2, double y2)
{
	double	deltaX;
	double	deltaY;
	double	step;
	
	x1 = round(x1);
	y1 = round(y1);
	x2 = round(x2);
	y2 = round(y2);
	deltaX = x2 - x1;
	deltaY = y2 - y1;
	step = (fabs(deltaX) > fabs(deltaY)) ? fabs(deltaX) : fabs(deltaY);
	deltaX /= step;
	deltaY /= step;
	while (fabs(x2 - x1) > 0.01 || fabs(y2 - y1) > 0.01)
	{
		map.addr[TO_COORD(x1, y1)] = 0xb3b3b3;
		x1 += deltaX;
		y1 += deltaY;
	}
}