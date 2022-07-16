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

	(void)data;
	if (keycode == KEY_ESC)
		close_window();
	else if (keycode == KEY_W)
	{
		player.walk_direction = 1;
		move_step = player.walk_direction * player.move_speed;
		new_x = player.pos.x + cos(player.rotation_angle) * move_step;
		new_y = player.pos.y + sin(player.rotation_angle) * move_step;
		if (!has_wall(data, new_x, new_y))
		{
			player.pos.x = new_x;
			player.pos.y = new_y;
		}
	}
	else if (keycode == KEY_A)
		player.turn_direction = -1;
	else if (keycode == KEY_S)
	{
		player.walk_direction = -1;
		move_step = player.walk_direction * player.move_speed;
		new_x = player.pos.x + cos(player.rotation_angle) * move_step;
		new_y = player.pos.y + sin(player.rotation_angle) * move_step;
		if (!has_wall(data, new_x, new_y))
		{
			player.pos.x = new_x;
			player.pos.y = new_y;
		}
	}
	else if (keycode == KEY_D)
		player.turn_direction = 1;
	player.rotation_angle += player.turn_direction * player.rotation_speed;
	player.turn_direction = 0;
	player.walk_direction = 0;
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
