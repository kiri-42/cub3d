#include "debug.h"

static void	dinit_map_data(t_game_data *data)
{
	map.img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	map.addr = (int *)mlx_get_data_addr(map.img, &map.bits_per_pixel, &map.line_lenght, &map.endian);
}

void	dinit_player(void)
{
	player.p_coord.x = WIDTH / 2;
	player.p_coord.y = HEIGHT / 2;
	player.radius = 3;
	player.turnDirection = 0;	/* -1 if left, +1 if right */
	player.walkDirection = 0;	/* -1 if back, +1 if front */
	player.rotationAngle = M_PI / 2;
	player.moveSpeed = 2.0;
	player.rotationSpeed = 3 * (M_PI / 180);
}

void	dinit_map(t_game_data *data)
{
	int win_x;
	int	win_y;

	data->mlx = mlx_init();
	if (!data->mlx)
		exit(EXIT_FAILURE);
	mlx_get_screen_size(data->mlx, &win_x, &win_y);
	if (0)
		exit(EXIT_FAILURE);
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, TITLE);
	if (!data->win)
		exit(EXIT_FAILURE);
	dinit_map_data(data);
	return ;
}
