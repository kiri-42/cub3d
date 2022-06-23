#include "debug.h"
#include <string.h>
#include <math.h>


void	draw_line(int *addr, double x1, double y1, double x2, double y2)
{
	double	deltaX;
	double	deltaY;
	double	step;

	deltaX = x2 - x1;
	deltaY = y2 - y1;
	step = (fabs(deltaX) > fabs(deltaY)) ? fabs(deltaX) : fabs(deltaY);
	deltaX /= step;
	deltaY /= step;
	while (fabs(x2 - x1) > 0.01 || fabs(y2 - y1) > 0.01)
	{
		addr[TO_COORD(x1, y1)] = LINE_RGB;
		x1 += deltaX;
		y1 += deltaY;
	}
}

void	set_line(double x1, double y1, double x2, double y2)
{
	int		*addr;
	int		bits_per_pixel;
	int		line_lenght;
	int		endian;

	addr = (int *)mlx_get_data_addr(map, &bits_per_pixel, &line_lenght, &endian);
	draw_line(addr, x1, y1, x2, y2);
}