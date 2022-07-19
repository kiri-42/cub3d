#include "cub3d.h"

double	normalize_angle(double angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle = (2 * M_PI) + angle;
	return (angle);
}

double	distance_between_points(double x1, double y1, double x2, double y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

t_direction	get_direction_of_line(double angle)
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
	t_coord	touch;
	t_coord	wall_hit;
	double	next;
	// int		map_y;

	*hit = false;
	next = 0;
	touch.x = intercept.x;
	touch.y = intercept.y;
	if (fov->d.up == true)
		next = -1;
	while (touch.x >= 0 && touch.x <= WIDTH && touch.y >= 0 && touch.y <= HEIGHT)
	{
		// map_y = floor(touch.y / TILE_SIZE);
		// if(data->map[map_y + (int)next] == NULL)
		// 	break;
		if (has_wall(data->map, touch.x, touch.y + next))
		{
			*hit = true;
			wall_hit.x = touch.x;
			wall_hit.y = touch.y;
			break ;
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
	t_coord	touch;
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
			break ;
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

	intercept.y = floor(player.pos.y / TILE_SIZE) * TILE_SIZE;
	if (d.down == 1)
		intercept.y += TILE_SIZE;
	intercept.x = player.pos.x + (intercept.y - player.pos.y) / tan(angle);
	return (intercept);
}

t_coord	get_vert_intercept(double angle, t_direction d)
{
	t_coord	intercept;

	intercept.x = floor(player.pos.x / TILE_SIZE) * TILE_SIZE;
	if (d.right == true)
		intercept.x += TILE_SIZE;
	intercept.y = player.pos.y + (intercept.x - player.pos.x) * tan(angle);
	return (intercept);
}

t_coord	get_horz_step(double angle, t_coord intercept, t_direction d)
{
	t_coord	step;

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
	t_coord	step;

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

double	found_horz_wall_hit(t_game_data *data, t_fov *fov, t_coord *coord)
{
	t_coord		intercept;
	t_coord		step;
	bool		is_hit;

	intercept = get_horz_intercept(fov->angle, fov->d);
	// printf("%s %d\n", __FILE__, __LINE__);
	step = get_horz_step(fov->angle, intercept, fov->d);
	// printf("%s %d\n", __FILE__, __LINE__);
	*coord = get_horz_touch_point(data, &is_hit, fov, intercept, step);
	// printf("%s %d\n", __FILE__, __LINE__);
	if (is_hit == false)
		return (DBL_MAX);
	else
		return (distance_between_points(player.pos.x, player.pos.y, coord->x, coord->y));
}

double	found_vert_wall_hit(t_game_data *data, t_fov *fov, t_coord *coord)
{
	t_coord		intercept;
	t_coord		step;
	bool		is_hit;

	intercept = get_vert_intercept(fov->angle, fov->d);
	step = get_vert_step(fov->angle, intercept, fov->d);
	*coord = get_vert_touch_point(data, &is_hit, fov, intercept, step);
	if (is_hit == false)
		return (DBL_MAX);
	else
		return (distance_between_points(player.pos.x, player.pos.y, coord->x, coord->y));
}

void	calc_one_ray(t_game_data *data, t_fov *fov)
{
	t_coord	h_wall_hit;
	t_coord	v_wall_hit;
	double	h_distance;
	double	v_distance;

	// printf("%s %d\n", __FILE__, __LINE__);
	fov->d = get_direction_of_line(fov->angle);
	// printf("%s %d\n", __FILE__, __LINE__);
	h_distance = found_horz_wall_hit(data, fov, &h_wall_hit);
	// printf("%s %d\n", __FILE__, __LINE__);
	v_distance = found_vert_wall_hit(data, fov, &v_wall_hit);
	// printf("%s %d\n", __FILE__, __LINE__);
	if (h_distance >= v_distance)
	{
		fov->distance = v_distance;
		fov->wall_hit.x = v_wall_hit.x;
		fov->wall_hit.y = v_wall_hit.y;
		fov->was_hit_vert = true;
	}
	else
	{
		fov->distance = h_distance;
		fov->wall_hit.x = h_wall_hit.x;
		fov->wall_hit.y = h_wall_hit.y;
		fov->was_hit_vert = false;
	}
}

void	cast_all_rays(t_game_data *data)
{
	double	ray_angle;
	size_t	i;

	ray_angle = player.rotation_angle - (FOV / 2);
	// ray_angle = player.rotation_angle;
	i = 0;
	while (i < RAYS)
	{
		// printf("%s %d\n", __FILE__, __LINE__);
		data->fov[i].id = i;
		data->fov[i].angle = normalize_angle(ray_angle);
		// printf("%s %d\n", __FILE__, __LINE__);
		calc_one_ray(data, &data->fov[i]);
		// printf("%s %d\n", __FILE__, __LINE__);
		ray_angle += (FOV / RAYS);
		i++;
	}
}
