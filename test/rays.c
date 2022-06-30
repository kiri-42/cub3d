#include "debug.h"

double	normalize_angle(double angle)
{
	// angle = angle % (2 * M_PI);
	angle = fmod(angle, 2 * M_PI);
	// angle = angle % (2*M_PI);
	if (angle < 0)
	{
		angle = (2 * M_PI) + angle;
	}
	return (angle);
}

double distance_between_points(double x1, double y1, double x2, double y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

t_direction get_direction_of_line(double angle)
{
	t_direction	d;

	ft_memset(&d, false, sizeof(t_direction));
	if (angle > 0 && angle < M_PI)
		d.down = 1;
	if (d.down != 1)
		d.up = 1;
	if (angle < 0.5 * M_PI || angle > 1.5 * M_PI)
		d.right = 1;
	if (d.right != 1)
		d.left = 1;
	return (d);
}

double	horz_wall_distance(t_game_data *data, double angle, int id)
{
	t_coord		wall_hit;
	t_coord		intercept;
	t_coord		step;
	t_direction	d;

	angle = normalize_angle(angle);
	d = get_direction_of_line(angle);

	intercept.y = floor(player.y / TILE_SIZE) * TILE_SIZE;
	if (d.down == 1)
		intercept.y += TILE_SIZE;
	intercept.x = player.x + (intercept.y - player.y) / tan(angle);

	step.y = TILE_SIZE;
	if (d.up == 1)
		step.y *= -1;

	step.x = TILE_SIZE / tan(angle);
	if (d.left == 1 && step.x > 0)
		step.x *= -1;
	if (d.right == 1 && step.x < 0)
		step.x *= -1;

	double horz_touch_x = intercept.x;
	double horz_touch_y = intercept.y;
	bool	horz_wall_hit = false;

	if (d.up)
		horz_touch_y--;

	while (horz_touch_x >= 0 && horz_touch_x <= WIDTH && horz_touch_y >= 0 && horz_touch_y <= HEIGHT)
	{
		if (has_wall(data->map, horz_touch_x, horz_touch_y))
		{
			horz_wall_hit = true;
			wall_hit.x = horz_touch_x;
			wall_hit.y = horz_touch_y;
			draw_line(map, player.x, player.y, wall_hit.x, wall_hit.y);
			break;
		}
		else
		{
			horz_touch_x += step.x;
			horz_touch_y += step.y;
		}
	}
	return (distance_between_points(player.x, player.y, wall_hit.x, wall_hit.y));
}

void	cast_all_rays(t_game_data *data)
{
	double rayAngle;
	int		column_id;
	size_t	i;

	double	d;

	column_id = 0;
	rayAngle = player.rotationAngle - (FOV / 2);
	i = 0;
	while (i < RAYS)
	{
		d = horz_wall_distance(data, rayAngle, column_id);
		printf("%f\n", d);
		// cast(player.rotationAngle, 0);
		// draw_line(map, player.x, player.y, player.x+cos(player.rotationAngle)*30, player.y+sin(player.rotationAngle)*30);
		// return;
		
		// draw_line(map, player.x, player.y, player.x+cos(rayAngle)*30, player.y+sin(rayAngle)*30);
		rayAngle += (FOV / RAYS);
		i++;
		column_id++;
		break;
	}
}