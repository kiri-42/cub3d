#include "cub3d.h"

static void	dinit_map_data(t_game_data *data)
{
	int	i;

	i = 0;
	map.ptr = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	map.addr = (int *)mlx_get_data_addr(map.ptr, &map.bits_per_pixel, &map.line_lenght, &map.endian);
	while (i < WIDTH * HEIGHT)
	{
		map.addr[i++] = 0xFFFFFF;
	}
}

void	dinit_player(void)
{
	player.pos.x = WIDTH / 2;
	player.pos.y = HEIGHT / 7;
	player.radius = 3;
	player.turn_direction = 0;	/* -1 if left, +1 if right */
	player.walk_direction = 0;	/* -1 if back, +1 if front */
	player.rotation_angle = M_PI / 2;
	player.move_speed = 5.0;
	player.rotation_speed = 3 * (M_PI / 180);
}

void	dinit_map(t_game_data *data)
{
	int	win_x;
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
	init_north_tex(data, &data->imgs);
	return ;
}
