#include "debug.h"

void	cast_all_rays()
{
	double rayAngle;
	size_t	i;

	rayAngle = player.rotationAngle - (FOV / 2);
	i = 0;
	while (i < RAYS)
	{
		draw_line(map, player.x, player.y, player.x+cos(rayAngle)*30, player.y+sin(rayAngle)*30);
		rayAngle += (FOV / RAYS);
		i++;
	}
}