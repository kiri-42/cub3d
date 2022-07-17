#include "cub3d.h"

int	close_window(void)
{
	exit(EXIT_SUCCESS);
}

int	key_hook(int keycode, t_game_data *data)
{
	double	move_step;
	double	new_x;
	double	new_y;
	t_player_data	*p;

	p = &data->player;
	(void)data;
	if (keycode == KEY_ESC)
		close_window();
	else if (keycode == KEY_W)
	{
		p->walk_direction = 1;
		move_step = p->walk_direction * p->move_speed;
		new_x = p->pos.x + cos(p->rotation_angle) * move_step;
		new_y = p->pos.y + sin(p->rotation_angle) * move_step;
		if (!has_wall(data, new_x, new_y))
		{
			p->pos.x = new_x;
			p->pos.y = new_y;
		}
	}
	else if (keycode == KEY_A)
		p->turn_direction = -1;
	else if (keycode == KEY_S)
	{
		p->walk_direction = -1;
		move_step = p->walk_direction * p->move_speed;
		new_x = p->pos.x + cos(p->rotation_angle) * move_step;
		new_y = p->pos.y + sin(p->rotation_angle) * move_step;
		if (!has_wall(data, new_x, new_y))
		{
			p->pos.x = new_x;
			p->pos.y = new_y;
		}
	}
	else if (keycode == KEY_D)
		p->turn_direction = 1;
	p->rotation_angle += p->turn_direction * p->rotation_speed;
	p->turn_direction = 0;
	p->walk_direction = 0;
	return (0);
}

int	loop_hook(t_game_data *data)
{
	render_all(data);
	// map.addr[TO_COORD(player.p_coord.x, player.p_coord.y)] = 0xFF0000;
	mlx_put_image_to_window(data->mlx, data->win, map.ptr, 0, 0);
	return (0);
}

void	loop_start(t_game_data *data)
{
	mlx_hook(data->win, 2, 1L << 0, key_hook, data);
	mlx_hook(data->win, 17, 0, close_window, NULL);
	mlx_loop_hook(data->mlx, loop_hook, data);
	mlx_loop(data->mlx);
}
