#include "cub3d.h"

void	init_map(t_game_data *data)
{
	int win_x;
	int	win_y;

	data->mlx = mlx_init();
	if (!data->mlx)
		exit(EXIT_FAILURE);
	mlx_get_screen_size(data->mlx, &win_x, &win_y);
	if (0)
		exit(EXIT_FAILURE);
	data->win = mlx_new_window(data->mlx, 320, 200, TITLE);
	if (!data->win)
		exit(EXIT_FAILURE);
	return ;
}
