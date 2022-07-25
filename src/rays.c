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

// void	tmp(t_game_data *data, t_fov *fov, t_ray *ray, t_coord *intercept, t_coord *next, t_coord *step)
// {
// 	if (has_wall(data, intercept->x + next->x, \
// 	intercept->y + next->y, MAP_WALL))
// 	{
// 		ray->is_hit_door = false;
// 		ray->hit = *intercept;
// 		ray->distance = distance_between_points(data->player.pos, ray->hit);
// 		return ;
// 	}
// 	if (has_wall(data, intercept->x + next->x, \
// 	intercept->y + next->y, MAP_DOOR))
// 	{
// 		ray->is_hit_door = true;
// 		fov->door_hit = add_coord(*intercept, *next);
// 		ray->hit = *intercept;
// 		ray->distance = distance_between_points(data->player.pos, ray->hit);
// 		return ;
// 	}
// 	else
// 		*intercept = add_coord(*intercept, *step);
// }

void	get_distance(t_game_data *data, t_fov *fov, t_ray *ray, int hv)
{
	t_coord	intercept;
	t_coord	step;
	t_coord	next;
	bool	first_hit_opened_door;

	ft_memset(&next, 0, sizeof(t_coord));
	first_hit_opened_door = false;
	step = get_step(fov->angle, fov->d, hv);
	intercept = get_intercept(&data->player, fov->angle, fov->d, hv);
	if (hv == HORIZONTAL && fov->d.up == true)
		next.y = -1;
	else if (hv == VERTICAL && fov->d.left == true)
		next.x = -1;
	while (intercept.x >= 0 && intercept.x <= data->map_width
		&& intercept.y >= 0 && intercept.y <= data->map_height)
	{
		// tmp(data, fov, ray, &intercept, &step, &next);
		if (has_wall(data, intercept.x + next.x, \
		intercept.y + next.y, MAP_WALL))
		{
			ray->is_hit_door = false;
			ray->hit = intercept;
			ray->distance = distance_between_points(data->player.pos, ray->hit);
			return ;
		}
		if (has_wall(data, intercept.x + next.x, \
		intercept.y + next.y, MAP_DOOR))
		{
			if (first_hit_opened_door == false)
			{
				ray->touching_door = add_coord(intercept, next);
				first_hit_opened_door = true;
			}
			if (data->map2[(int)floor((intercept.y + next.y) / TILE_SIZE)][(int)floor((intercept.x + next.x) / TILE_SIZE)].door_open == CLOSE)
			{
				ray->is_hit_door = true;
				ray->hit = intercept;
				ray->distance = distance_between_points(data->player.pos, ray->hit);
				return ;
			}
		}
		intercept = add_coord(intercept, step);
	}
	ray->distance = DBL_MAX;
	return ;
}

void	calc_one_ray(t_game_data *data, t_fov *fov)
{
	t_ray	h;
	t_ray	v;

	ft_memset(&h, 0, sizeof(t_ray));
	ft_memset(&v, 0, sizeof(t_ray));
	fov->d = get_direction_of_line(fov->angle);
	get_distance(data, fov, &h, HORIZONTAL);
	get_distance(data, fov, &v, VERTICAL);
	if (h.distance >= v.distance)
	{
		fov->distance = v.distance;
		fov->wall_hit = v.hit;
		fov->was_hit_vert = true;
		fov->is_door = v.is_hit_door;
		if ((size_t)fov->id == data->ray / 2)
		{
			data->touching_door = get_door_status(data->map2, v.touching_door);
			data->touching_door_distance = distance_between_points(data->player.pos, v.touching_door);
			if (data->touching_door_distance < TILE_SIZE)
				data->is_touching_door = true;
			else
			{
				data->touching_door_distance = 0;
				data->is_touching_door = false;
			}
		}
	}
	else
	{
		fov->distance = h.distance;
		fov->wall_hit = h.hit;
		fov->was_hit_vert = false;
		fov->is_door = h.is_hit_door;
		if ((size_t)fov->id == data->ray / 2)
		{
			data->touching_door = get_door_status(data->map2, h.touching_door);
			data->touching_door_distance = distance_between_points(data->player.pos, h.touching_door);
			if (data->touching_door_distance < TILE_SIZE)
				data->is_touching_door = true;
			else
			{
				data->touching_door_distance = 0;
				data->is_touching_door = false;
			}
		}
	}
}

void	cast_all_rays(t_game_data *data)
{
	double	ray_angle;
	size_t	i;

	ray_angle = data->player.rotation_angle - (FOV / 2);
	i = 0;
	data->touching_door = NULL;
	while (i < (size_t)data->ray)
	{
		data->fov[i].id = i;
		data->fov[i].angle = normalize_angle(ray_angle);
		calc_one_ray(data, &data->fov[i]);
		ray_angle += (FOV / data->ray);
		i++;
	}
}
