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

void	get_horz_touch_point(t_game_data *data, t_fov *fov, t_ray *h)
{
	t_coord	touch;
	t_coord	wall_hit;
	double	next;

	h->is_hit = false;
	next = 0;
	touch.x = h->intercept.x;
	touch.y = h->intercept.y;
	if (fov->d.up == true)
		next = -1;
	while (touch.x >= 0 && touch.x <= data->map_width && touch.y >= 0 && touch.y <= data->map_height)
	{
		if (has_wall(data, touch.x, touch.y + next))
		{
			h->is_hit = true;
			wall_hit.x = touch.x;
			wall_hit.y = touch.y;
			break ;
		}
		else
		{
			touch.x += h->step.x;
			touch.y += h->step.y;
		}
	}
	h->wall_hit = wall_hit;
}

void	get_vert_touch_point(t_game_data *data, t_fov *fov, t_ray *v)
{
	t_coord	touch;
	t_coord	wall_hit;
	double	next;

	v->is_hit = false;
	next = 0;
	touch.x = v->intercept.x;
	touch.y = v->intercept.y;
	if (fov->d.left == true)
		next = -1;
	while (touch.x >= 0 && touch.x <= data->map_width && touch.y >= 0 && touch.y <= data->map_height)
	{
		if (has_wall(data, touch.x + next, touch.y))
		{
			v->is_hit = true;
			wall_hit.x = touch.x;
			wall_hit.y = touch.y;
			break ;
		}
		else
		{
			touch.x += v->step.x;
			touch.y += v->step.y;
		}
	}
	v->wall_hit = wall_hit;
}

t_coord	get_horz_intercept(t_player_data *p, double angle, t_direction d)
{
	t_coord	intercept;

	intercept.y = floor(p->pos.y / TILE_SIZE) * TILE_SIZE;
	if (d.down == 1)
		intercept.y += TILE_SIZE;
	intercept.x = p->pos.x + (intercept.y - p->pos.y) / tan(angle);
	return (intercept);
}

t_coord	get_vert_intercept(t_player_data *p, double angle, t_direction d)
{
	t_coord	intercept;

	intercept.x = floor(p->pos.x / TILE_SIZE) * TILE_SIZE;
	if (d.right == true)
		intercept.x += TILE_SIZE;
	intercept.y = p->pos.y + (intercept.x - p->pos.x) * tan(angle);
	return (intercept);
}

t_coord	get_horz_step(double angle, t_direction d)
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

t_coord	get_vert_step(double angle, t_direction d)
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

void	found_horz_wall_hit(t_game_data *data, t_fov *fov, t_ray *h)
{
	h->intercept = get_horz_intercept(&data->player, fov->angle, fov->d);
	h->step = get_horz_step(fov->angle, fov->d);
	get_horz_touch_point(data, fov, h);
	if (h->is_hit == false)
		h->distance = DBL_MAX;
	else
		h->distance = distance_between_points(data->player.pos.x, data->player.pos.y, h->wall_hit.x, h->wall_hit.y);
}

void	found_vert_wall_hit(t_game_data *data, t_fov *fov, t_ray *v)
{
	v->intercept = get_vert_intercept(&data->player, fov->angle, fov->d);
	v->step = get_vert_step(fov->angle, fov->d);
	get_vert_touch_point(data, fov, v);
	if (v->is_hit == false)
		v->distance = DBL_MAX;
	else
		v->distance = distance_between_points(data->player.pos.x, data->player.pos.y, v->wall_hit.x, v->wall_hit.y);
}

void	calc_one_ray(t_game_data *data, t_fov *fov)
{
	t_ray	h;
	t_ray	v;

	fov->d = get_direction_of_line(fov->angle);
	found_horz_wall_hit(data, fov, &h);
	found_vert_wall_hit(data, fov, &v);
	if (h.distance >= v.distance)
	{
		fov->distance = v.distance;
		fov->wall_hit.x = v.wall_hit.x;
		fov->wall_hit.y = v.wall_hit.y;
		fov->was_hit_vert = true;
	}
	else
	{
		fov->distance = h.distance;
		fov->wall_hit.x = h.wall_hit.x;
		fov->wall_hit.y = h.wall_hit.y;
		fov->was_hit_vert = false;
	}
}

void	cast_all_rays(t_game_data *data)
{
	double	ray_angle;
	size_t	i;

	ray_angle = data->player.rotation_angle - (FOV / 2);
	i = 0;
	while (i < (size_t)data->ray)
	{
		data->fov[i].id = i;
		data->fov[i].angle = normalize_angle(ray_angle);
		calc_one_ray(data, &data->fov[i]);
		ray_angle += (FOV / data->ray);
		i++;
	}
}
