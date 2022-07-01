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

t_coord	get_horz_intercept(double angle, t_direction d)
{
	t_coord	intercept;

	intercept.y = floor(player.y / TILE_SIZE) * TILE_SIZE;
	if (d.down == 1)
		intercept.y += TILE_SIZE;
	intercept.x = player.x + (intercept.y - player.y) / tan(angle);
	return (intercept);
}

t_coord	get_vert_intercept(double angle, t_direction d)
{
	t_coord	intercept;

	intercept.x = floor(player.x / TILE_SIZE) * TILE_SIZE;
	if (d.right == true)
		intercept.x += TILE_SIZE;
	intercept.y = player.y + (intercept.x - player.x) * tan(angle);
	return (intercept);
}

t_coord	get_horz_step(double angle, t_coord intercept, t_direction d)
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

t_coord	get_vert_step(double angle, t_coord intercept, t_direction d)
{
	t_coord step;

	step.x = TILE_SIZE;
	if (d.left == true)
		step.x *= -1;
	step.y = TILE_SIZE * tan(angle);
	if (d.up == 1 && step.y > 0)
		step.y *= -1;
	if (d.down == 1 && step.y < 0)
		step.y *= -1;
	return (step);
}

t_coord	get_horz_wall_hit(t_game_data *data, double angle, t_direction d, int id)
{
	t_coord		wall_hit;
	t_coord		intercept;
	t_coord		step;

	intercept = get_horz_intercept(angle, d);
	step = get_horz_step(angle, intercept, d);
	if (d.up == true)
		intercept.y--;
	return (get_touch_point(data, intercept, step));
}

t_coord	get_vert_wall_hit(t_game_data *data, double angle, t_direction d, int id)
{
	t_coord		wall_hit;
	t_coord		intercept;
	t_coord		step;

	intercept = get_vert_intercept(angle, d);
	step = get_vert_step(angle, intercept, d);
	if (d.left == true)
		intercept.x--;
	return (get_touch_point(data, intercept, step));
}

void	get_wall_hit(t_game_data *data, double angle, int id)
{
	t_direction	d;
	t_coord	horz;
	t_coord	vert;
	double	horz_d;
	double	vert_d;

	angle = normalize_angle(angle);
	d = get_direction_of_line(angle);
	horz = get_horz_wall_hit(data, angle, d, id);
	vert = get_vert_wall_hit(data, angle, d, id);
	horz_d = distance_between_points(player.x, player.y, horz.x, horz.y);
	vert_d = distance_between_points(player.x, player.y, vert.x, vert.y);
	if (horz_d >= vert_d)
		draw_line(map, player.x, player.y, vert.x, vert.y);
	else
		draw_line(map, player.x, player.y, horz.x, horz.y);

}

void	cast_all_rays(t_game_data *data)
{
	double rayAngle;
	int		column_id;
	size_t	i;

	double	d;

	column_id = 0;
	// rayAngle = player.rotationAngle - (FOV / 2);
	rayAngle = player.rotationAngle;
	i = 0;
	while (i < 1)
	{
		get_wall_hit(data, rayAngle, column_id);
		rayAngle += (FOV / RAYS);
		i++;
		column_id++;
		break;
	}
}