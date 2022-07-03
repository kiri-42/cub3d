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

t_coord	get_touch_point(t_game_data *data, bool *hit, t_coord intercept, t_coord step)
{
	t_coord touch;
	t_coord	wall_hit;

	*hit = false;
	touch.x = intercept.x;
	touch.y = intercept.y;
	while (touch.x >= 0 && touch.x <= WIDTH && touch.y >= 0 && touch.y <= HEIGHT)
	{
		if (has_wall(data->map, touch.x, touch.y))
		{
			*hit = true;
			wall_hit.x = touch.x;
			wall_hit.y = touch.y;
			break;
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

void	get_horz_wall_hit(t_game_data *data, double angle, t_fov *fov, int id)
{
	t_coord		intercept;
	t_coord		step;

	intercept = get_horz_intercept(angle, fov->d);
	step = get_horz_step(angle, intercept, fov->d);
	if (fov->d.up == true)
		intercept.y--;
	fov->h_wall_hit = get_touch_point(data, &fov->h_is_hit, intercept, step);
}

void	get_vert_wall_hit(t_game_data *data, double angle, t_fov *fov, int id)
{
	t_coord		intercept;
	t_coord		step;

	intercept = get_vert_intercept(angle, fov->d);
	step = get_vert_step(angle, intercept, fov->d);
	if (fov->d.left == true)
		intercept.x--;
	fov->v_wall_hit = get_touch_point(data, &fov->v_is_hit, intercept, step);
}

void	get_wall_hit(t_game_data *data, double angle, int id)
{
	t_fov	fov;
	t_coord	horz;
	t_coord	vert;
	double	horz_d;
	double	vert_d;

	ft_memset(&fov, 0, sizeof(t_fov));
	fov.id = id;
	fov.angle = normalize_angle(angle);
	fov.d = get_direction_of_line(fov.angle);
	get_horz_wall_hit(data, angle, &fov, id);
	get_vert_wall_hit(data, angle, &fov, id);
	horz_d = distance_between_points(player.x, player.y, fov.h_wall_hit.x, fov.h_wall_hit.y);
	vert_d = distance_between_points(player.x, player.y, fov.v_wall_hit.x, fov.v_wall_hit.y);
	if (horz_d >= vert_d || (fov.h_is_hit == false && fov.v_is_hit == true))
		draw_line(map, player.x, player.y, fov.v_wall_hit.x, fov.v_wall_hit.y);
	else
		draw_line(map, player.x, player.y, fov.h_wall_hit.x, fov.h_wall_hit.y);

}

void	cast_all_rays(t_game_data *data)
{
	double rayAngle;
	int		column_id;
	size_t	i;

	double	d;

	column_id = 0;
	rayAngle = player.rotationAngle - (FOV / 2);
	// rayAngle = player.rotationAngle;
	i = 0;
	while (i < RAYS)
	{
		get_wall_hit(data, rayAngle, column_id);
		rayAngle += (FOV / RAYS);
		i++;
		column_id++;
		// break;
	}
}