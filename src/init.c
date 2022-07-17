#include "cub3d.h"

void	init_player(t_game_data *data)
{
	data->player.pos.x = data->width / 2;
	data->player.pos.y = data->height / 7;
	data->player.radius = 3;
	data->player.turn_direction = 0;	/* -1 if left, +1 if right */
	data->player.walk_direction = 0;	/* -1 if back, +1 if front */
	data->player.rotation_angle = M_PI / 2;
	data->player.move_speed = 5.0;
	data->player.rotation_speed = 3 * (M_PI / 180);
}

void	set_map_data(t_game_data *gd)
{
	size_t	rows;
	size_t	cols;
	size_t	len;

	rows = 0;
	cols = 0;
	while (gd->map[rows])
	{
		len = ft_strlen(gd->map[rows]);
		if (len > cols)
			cols = len;
		rows++;
	}
	gd->rows = rows;
	gd->cols = cols;
	gd->width = cols * TILE_SIZE;
	gd->height = rows * TILE_SIZE;
	gd->ray = gd->width / WALL_STRIP_WIDTH;
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
	data->win = mlx_new_window(data->mlx, data->width, data->height, TITLE);
	if (!data->win)
		exit(EXIT_FAILURE);
	map.ptr = mlx_new_image(data->mlx, data->width, data->height);
	map.addr = (int *)mlx_get_data_addr(map.ptr, &map.bits_per_pixel, &map.line_lenght, &map.endian);
}
