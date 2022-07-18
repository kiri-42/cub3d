#include "cub3d.h"

void	init_player_param(t_game_data *data)
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

void	init_mlx(t_game_data *data)
{
	int			win_x;
	int			win_y;
	t_img_data	*m;

	m = &data->map_img_data; 
	data->mlx = mlx_init();
	if (!data->mlx)
		exit(EXIT_FAILURE);
	mlx_get_screen_size(data->mlx, &win_x, &win_y);
	if (0)
		exit(EXIT_FAILURE);
	data->win = mlx_new_window(data->mlx, data->width, data->height, TITLE);
	if (!data->win)
		exit(EXIT_FAILURE);
	m->ptr = mlx_new_image(data->mlx, data->width, data->height);
	m->addr = (int *)mlx_get_data_addr(m->ptr, &m->bits_per_pixel, &m->line_lenght, &m->endian);
}

bool	open_tex(t_game_data *data, t_imgs *img)
{
	img->wall_north.ptr = mlx_xpm_file_to_image(data->mlx, data->tp.no_path, &img->wall_north.width, &img->wall_north.height);
	img->wall_north.addr = (int *)mlx_get_data_addr(img->wall_north.ptr, &img->wall_north.bits_per_pixel, &img->wall_north.line_lenght, &img->wall_north.endian);
	img->wall_south.ptr = mlx_xpm_file_to_image(data->mlx, data->tp.so_path, &img->wall_south.width, &img->wall_south.height);
	img->wall_south.addr = (int *)mlx_get_data_addr(img->wall_south.ptr, &img->wall_south.bits_per_pixel, &img->wall_south.line_lenght, &img->wall_south.endian);
	img->wall_east.ptr = mlx_xpm_file_to_image(data->mlx, data->tp.ea_path, &img->wall_east.width, &img->wall_east.height);
	img->wall_east.addr = (int *)mlx_get_data_addr(img->wall_east.ptr, &img->wall_east.bits_per_pixel, &img->wall_east.line_lenght, &img->wall_east.endian);
	img->wall_west.ptr = mlx_xpm_file_to_image(data->mlx, data->tp.we_path, &img->wall_west.width, &img->wall_west.height);
	img->wall_west.addr = (int *)mlx_get_data_addr(img->wall_west.ptr, &img->wall_west.bits_per_pixel, &img->wall_west.line_lenght, &img->wall_west.endian);
	return (true);
}
