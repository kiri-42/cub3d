#include "cub3d.h"

void	loop_start(t_game_data *data)
{
	mlx_key_hook(data->win, key_hook, data);
	mlx_hook(data->win, 17, 0, close_window, NULL);
	mlx_loop(data->mlx);
}
