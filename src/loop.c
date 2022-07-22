#include "cub3d.h"

int	close_window(void *data)
{
	t_game_data	*gd;

	gd = data;
	free_all(gd);
	exit(EXIT_SUCCESS);
}

void	run_KEY_W(t_player_data	*p, t_game_data *data, t_move *m)
{
	p->walk_direction = 1;
	m->move_step = p->walk_direction * p->move_speed;
	m->new_x = p->pos.x + cos(p->rotation_angle) * m->move_step;
	m->new_y = p->pos.y + sin(p->rotation_angle) * m->move_step;
	if (!has_wall(data, m->new_x, m->new_y))
	{
		p->pos.x = m->new_x;
		p->pos.y = m->new_y;
	}
}

// TODO 3つのdouble変数を構造体でまとめたい
int	key_hook(int keycode, t_game_data *data)
{
	t_move			m;
	t_player_data	*p;

	p = &data->player;
	if (keycode == KEY_ESC)
		close_window(data);
	else if (keycode == KEY_W)
		run_KEY_W(p, data,  &m);
	else if (keycode == KEY_A)
		p->turn_direction = -1;
	else if (keycode == KEY_S)
	{
		p->walk_direction = -1;
		m.move_step = p->walk_direction * p->move_speed;
		m.new_x = p->pos.x + cos(p->rotation_angle) * m.move_step;
		m.new_y = p->pos.y + sin(p->rotation_angle) * m.move_step;
		if (!has_wall(data, m.new_x, m.new_y))
		{
			p->pos.x = m.new_x;
			p->pos.y = m.new_y;
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
	mlx_put_image_to_window(data->mlx, data->win, data->map_img_data.ptr, 0, 0);
	return (0);
}

void	loop_start(t_game_data *data)
{
	mlx_hook(data->win, 2, 1L << 0, key_hook, data);
	mlx_hook(data->win, 17, 0, close_window, data);
	mlx_loop_hook(data->mlx, loop_hook, data);
	mlx_loop(data->mlx);
}
