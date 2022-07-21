#include "cub3d.h"

t_coord	get_intercept(t_player_data *p, double angle, t_direction d, int hv)
{
	t_coord	intercept;

	if (hv == HORIZONTAL)
	{
		intercept.y = floor(p->pos.y / TILE_SIZE) * TILE_SIZE;
		if (d.down == 1)
			intercept.y += TILE_SIZE;
		intercept.x = p->pos.x + (intercept.y - p->pos.y) / tan(angle);
	}
	else
	{
		intercept.x = floor(p->pos.x / TILE_SIZE) * TILE_SIZE;
		if (d.right == true)
			intercept.x += TILE_SIZE;
		intercept.y = p->pos.y + (intercept.x - p->pos.x) * tan(angle);
	}
	return (intercept);
}

t_coord	get_step(double angle, t_direction d, int hv)
{
	t_coord	step;

	if (hv == HORIZONTAL)
	{
		step.x = TILE_SIZE / tan(angle);
		step.y = TILE_SIZE;
		if (d.up == 1)
			step.y *= -1;
		if ((d.left == 1 && step.x > 0) || (d.right == 1 && step.x < 0))
			step.x *= -1;
	}
	else
	{
		step.x = TILE_SIZE;
		step.y = TILE_SIZE * tan(angle);
		if (d.left == true)
			step.x *= -1;
		if ((d.up == 1 && step.y > 0) || (d.down == 1 && step.y < 0))
			step.y *= -1;
	}
	return (step);
}

double	get_distance(t_game_data *data, t_fov *fov, t_coord *coord, int hv)
{
	t_coord	intercept;
	t_coord	step;
	t_coord	next;

	ft_memset(&next, 0, sizeof(t_coord));
	step = get_step(fov->angle, fov->d, hv);
	intercept = get_intercept(&data->player, fov->angle, fov->d, hv);
	if (hv == HORIZONTAL && fov->d.up == true)
		next.y = -1;
	else if (hv == VERTICAL && fov->d.left == true)
		next.x = -1;
	while (intercept.x >= 0 && intercept.x <= data->map_width
		&& intercept.y >= 0 && intercept.y <= data->map_height)
	{
		if (has_wall(data, intercept.x + next.x, intercept.y + next.y))
		{
			*coord = intercept;
			return (distance_between_points(data->player.pos, *coord));
		}
		else
			intercept = add_coord(intercept, step);
	}
	return (DBL_MAX);
}

void	calc_one_ray(t_game_data *data, t_fov *fov)
{
	t_coord	h;
	t_coord	v;
	double	h_distance;
	double	v_distance;

	fov->d = get_direction_of_line(fov->angle);
	h_distance = get_distance(data, fov, &h, HORIZONTAL);
	v_distance = get_distance(data, fov, &v, VERTICAL);
	if (h_distance >= v_distance)
	{
		fov->distance = v_distance;
		fov->wall_hit = v;
		fov->was_hit_vert = true;
	}
	else
	{
		fov->distance = h_distance;
		fov->wall_hit = h;
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
