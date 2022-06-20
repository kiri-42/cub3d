#include "cub3d.h"
#include "debug.h"

int	dclose_window(void)
{
	exit(EXIT_SUCCESS);
}

int	dkey_hook(int keycode, t_game_data *data)
{
	(void)data;
	if (keycode == KEY_ESC)
		close_window();
	else if (keycode == KEY_W)
		player.y--;
	else if (keycode == KEY_A)
		player.x--;
	else if (keycode == KEY_S)
		player.y++;
	else if (keycode == KEY_D)
		player.x++;
	put_tile(data);
	return (0);
}

void	dloop_start(t_game_data *data)
{
	mlx_key_hook(data->win, dkey_hook, data);
	mlx_hook(data->win, 17, 0, dclose_window, NULL);
	mlx_loop(data->mlx);

	mlx_loop(mlx2);
}
