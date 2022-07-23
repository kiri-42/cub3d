#include "cub3d.h"

int	close_window(void *data)
{
	t_game_data	*gd;

	gd = data;
	free_all(gd);
	exit(EXIT_SUCCESS);
}

void	turn_player(t_game_data *data, t_move m)
{
	int	direction;

	direction = 1;
	if (m == LEFT)
		direction = -1;
	data->player.rotation_angle += data->player.rotation_speed * direction;
}

void	move_player(t_game_data *data, t_move m)
{
	double			move_step;
	double			new_x;
	double			new_y;
	t_player_data	*p;

	p = &data->player;
	move_step = p->move_speed;
	if (m == BACK || m == LEFT)
	move_step *= -1;
	if (m == FRONT || m == BACK)
	{
		new_x = p->pos.x + cos(p->rotation_angle) * move_step;
		new_y = p->pos.y + sin(p->rotation_angle) * move_step;
	}
	else
	{
		new_x = p->pos.x + cos(p->rotation_angle + M_PI / 2) * move_step;
		new_y = p->pos.y + sin(p->rotation_angle + M_PI / 2) * move_step;
	}
	if (!has_wall(data, new_x, new_y))
	{
		p->pos.x = new_x;
		p->pos.y = new_y;
	}
}

int	key_hook(int keycode, t_game_data *data)
{
	if (keycode == KEY_ESC)
		close_window(data);
	else if (keycode == KEY_W)
		move_player(data, FRONT);
	else if (keycode == KEY_A)
		move_player(data, LEFT);
	else if (keycode == KEY_S)
		move_player(data, BACK);
	else if (keycode == KEY_D)
		move_player(data, RIGHT);
	else if (keycode == KEY_RIGHT)
		turn_player(data, RIGHT);
	else if (keycode == KEY_LEFT)
		turn_player(data, LEFT);
	return (0);
}

int	mouse_hook(int button, int x, int y, void *data)
{
	t_game_data	*gd;
	size_t		ray_index;

	(void)y;
	if (button != MOUSE_LEFT)
		return (0);
	gd = data;
	ray_index = x * gd->ray / gd->win_width;
	if (ray_index > gd->ray)
		return (0);
	gd->player.rotation_angle = gd->fov[ray_index].angle;
	return (0);
}

int	loop_hook(t_game_data *data)
{
	render_all(data);
	mlx_put_image_to_window(data->mlx, data->win, data->map_img_data.ptr, 0, 0);
	return (0);
}

void	loop_start(t_game_data *data)
{
	mlx_mouse_hook(data->win, mouse_hook, data);
	mlx_hook(data->win, 2, 1L << 0, key_hook, data);
	mlx_hook(data->win, 17, 0, close_window, data);
	mlx_loop_hook(data->mlx, loop_hook, data);
	mlx_loop(data->mlx);
}
