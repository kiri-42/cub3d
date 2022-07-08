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

t_coord	get_horz_touch_point(t_game_data *data, bool *hit, t_fov *fov, t_coord intercept, t_coord step)
{
	t_coord touch;
	t_coord	wall_hit;
	double	next;

	*hit = false;
	next = 0;
	touch.x = intercept.x;
	touch.y = intercept.y;
	if (fov->d.up == true)
		next = -1;
	while (touch.x >= 0 && touch.x <= WIDTH && touch.y >= 0 && touch.y <= HEIGHT)
	{
		if (has_wall(data->map, touch.x, touch.y + next))
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

t_coord	get_vert_touch_point(t_game_data *data, bool *hit, t_fov *fov, t_coord intercept, t_coord step)
{
	t_coord touch;
	t_coord	wall_hit;
	double	next;

	*hit = false;
	next = 0;
	touch.x = intercept.x;
	touch.y = intercept.y;
	if (fov->d.left == true)
		next = -1;
	while (touch.x >= 0 && touch.x <= WIDTH && touch.y >= 0 && touch.y <= HEIGHT)
	{
		if (has_wall(data->map, touch.x + next, touch.y))
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

	intercept.y = floor(player.p_coord.y / TILE_SIZE) * TILE_SIZE;
	if (d.down == 1)
		intercept.y += TILE_SIZE;
	intercept.x = player.p_coord.x + (intercept.y - player.p_coord.y) / tan(angle);
	return (intercept);
}

t_coord	get_vert_intercept(double angle, t_direction d)
{
	t_coord	intercept;

	intercept.x = floor(player.p_coord.x / TILE_SIZE) * TILE_SIZE;
	if (d.right == true)
		intercept.x += TILE_SIZE;
	intercept.y = player.p_coord.y + (intercept.x - player.p_coord.x) * tan(angle);
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

void	found_horz_wall_hit(t_game_data *data, t_fov *fov)
{
	t_coord		intercept;
	t_coord		step;

	intercept = get_horz_intercept(fov->angle, fov->d);
	step = get_horz_step(fov->angle, intercept, fov->d);
	// if (fov->d.up == true)
	// 	intercept.y--;
	fov->h_wall_hit = get_horz_touch_point(data, &fov->h_is_hit, fov, intercept, step);
	if (fov->h_is_hit == false)
		fov->h_distance = DBL_MAX;
	else
		fov->h_distance = distance_between_points(player.p_coord.x, player.p_coord.y, fov->h_wall_hit.x, fov->h_wall_hit.y);
}

void	found_vert_wall_hit(t_game_data *data, t_fov *fov)
{
	t_coord		intercept;
	t_coord		step;

	intercept = get_vert_intercept(fov->angle, fov->d);
	step = get_vert_step(fov->angle, intercept, fov->d);
	// if (fov->d.left == true)
	// 	intercept.x--;
	fov->v_wall_hit = get_vert_touch_point(data, &fov->v_is_hit, fov, intercept, step);
	if (fov->v_is_hit == false)
		fov->v_distance = DBL_MAX;
	else
		fov->v_distance = distance_between_points(player.p_coord.x, player.p_coord.y, fov->v_wall_hit.x, fov->v_wall_hit.y);
}

void	draw_one_ray(t_game_data *data, double angle, int id)
{
	t_fov	fov;
	t_coord	start;
	t_coord goal;

	ft_memset(&fov, 0, sizeof(t_fov));
	fov.id = id;
	fov.angle = normalize_angle(angle);
	fov.d = get_direction_of_line(fov.angle);
	found_horz_wall_hit(data, &fov);
	found_vert_wall_hit(data, &fov);
	start.x = player.p_coord.x * MINIMAP_SCALE;
	start.y = player.p_coord.y * MINIMAP_SCALE;
	if (fov.h_distance >= fov.v_distance)
	{
		goal.x = fov.v_wall_hit.x * MINIMAP_SCALE;
		goal.y = fov.v_wall_hit.y * MINIMAP_SCALE;
		// draw_line(map, player.p_coord, fov.v_wall_hit);
	}
	else
	{
		goal.x = fov.h_wall_hit.x * MINIMAP_SCALE;
		goal.y = fov.h_wall_hit.y * MINIMAP_SCALE;
		// draw_line(map, player.p_coord, fov.h_wall_hit);
	}
	draw_line(data, start, goal, 0xFF0000);
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
		draw_one_ray(data, rayAngle, column_id);
		rayAngle += (FOV / RAYS);
		i++;
		column_id++;
	}
}
