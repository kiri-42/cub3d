#include "cub3d.h"

void	init_player(void)
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

void	init_map_data(t_game_data *gd)
{
	int	i;
	int	col;

	i = 0;
	col = 0;
	while (gd->map[i])
	{
		if (ft_strlen(gd->map[i]) > col)
			col = ft_strlen(gd->map[i]);
		i++;
	}
	gd->rows = i;
	gd->cols = col;
	gd->width = col * TILE_SIZE;
	gd->height = i * TILE_SIZE;
}

void	init_map(t_game_data *data)
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
	map.ptr = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	map.addr = (int *)mlx_get_data_addr(map.ptr, &map.bits_per_pixel, &map.line_lenght, &map.endian);
}
