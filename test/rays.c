#include "debug.h"

double	normalize_angle(double angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle = (2 * M_PI) + angle;
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
		d.down = true;
	else
		d.up = true;
	if (angle < 0.5 * M_PI || angle > 1.5 * M_PI)
		d.right = true;
	else
		d.left = true;
	return (d);
}

t_coord	get_touch_point(t_game_data *data, t_coord intercept, t_coord step)
{
	t_coord touch;
	t_coord	wall_hit;

	touch.x = intercept.x;
	touch.y = intercept.y;
	while (touch.x >= 0 && touch.x <= WIDTH && touch.y >= 0 && touch.y <= HEIGHT)
	{
		if (has_wall(data->map, touch.x, touch.y))
		{
			wall_hit.x = touch.x;
			wall_hit.y = touch.y;
			draw_line(map, player.x, player.y, touch.x, touch.y);
			return (wall_hit);
		}
		else
		{
			touch.x += step.x;
			touch.y += step.y;
		}
	}
	return (wall_hit);
}

t_coord	get_intercept(double angle, t_direction d)
{
	t_coord	intercept;

	intercept.y = floor(player.y / TILE_SIZE) * TILE_SIZE;
	if (d.down == 1)
		intercept.y += TILE_SIZE;
	intercept.x = player.x + (intercept.y - player.y) / tan(angle);
	return (intercept);
}

t_coord	get_step(double angle, t_coord intercept, t_direction d)
{
	t_coord step;

	step.y = TILE_SIZE;
	if (d.up == 1)
		step.y *= -1;
	step.x = TILE_SIZE / tan(angle);
	if (d.left == 1 && step.x > 0)
		step.x *= -1;
	if (d.right == 1 && step.x < 0)
		step.x *= -1;
	return (step);
}

t_coord	get_horz_wall_hit(t_game_data *data, double angle, int id)
{
	t_coord		wall_hit;
	t_coord		intercept;
	t_coord		step;
	t_direction	d;

	angle = normalize_angle(angle);
	d = get_direction_of_line(angle);
	intercept = get_intercept(angle, d);
	step = get_step(angle, intercept, d);
	if (d.up == true)
		intercept.y--;
	return (get_touch_point(data, intercept, step));
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
	while (i < 1)
	{
		get_horz_wall_hit(data, rayAngle, column_id);
		rayAngle += (FOV / RAYS);
		i++;
		column_id++;
		break;
	}
}