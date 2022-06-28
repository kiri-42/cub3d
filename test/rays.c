#include "debug.h"

double	normalize_angle(double angle)
{
	// angle = angle % (2 * M_PI);
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
	{
		angle = (2 * M_PI) + angle;
	}
	return (angle);
}

void	cast(double angle, int id)
{
	double ray_angle;
	double wall_hit_x = 0;
	double wall_hit_y = 0;
	double distance;
	double yintersept = 0;
	double xintersept = 0;

	double ystep;
	double xstep;

	int		is_up = 0;
	int		is_down = 0;
	int		is_right = 0;
	int		is_left = 0;

	ray_angle = normalize_angle(angle);

	if (ray_angle > 0 && ray_angle < M_PI)
		is_down = 1;
	if (is_down != 1)
		is_up = 1;
	if (ray_angle < 0.5 * M_PI || ray_angle > 1.5 * M_PI)
		is_right = 1;
	if (is_right != 1)
		is_left = 1;

	yintersept = floor(player.y / TILE_SIZE) * TILE_SIZE;
	if (is_down == 1)
		yintersept += TILE_SIZE;
	xintersept = player.x + (yintersept - player.y) / tan(ray_angle);

	ystep = TILE_SIZE;
	if (is_up == 1)
		ystep *= -1;

	xstep = TILE_SIZE / tan(ray_angle);
	if (is_left == 1 && xstep > 0)
		xstep *= -1;
	if (is_right == 1 && xstep < 0)
		xstep *= -1;

	draw_line(map, player.x, player.y, player.x+cos(ray_angle)*30, player.y+sin(ray_angle)*30);
	// printf("%f\n", ray_angle);
	if (is_right == 1)
		printf("%d true\n", is_right);
	else
		printf("%d false\n", is_right);
}

void	cast_all_rays()
{
	double rayAngle;
	int		column_id;
	size_t	i;

	column_id = 0;
	rayAngle = player.rotationAngle - (FOV / 2);
	i = 0;
	while (i < RAYS)
	{
		cast(rayAngle, column_id);
		
		// draw_line(map, player.x, player.y, player.x+cos(rayAngle)*30, player.y+sin(rayAngle)*30);
		rayAngle += (FOV / RAYS);
		i++;
		column_id++;
		break;
	}
}