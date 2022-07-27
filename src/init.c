#include "cub3d.h"

void	init_player_param(t_game_data *data)
{
	init_player_pos(data);
	data->player.radius = 15;
	data->player.move_speed = 5.0;
	data->player.rotation_speed = 3 * (M_PI / 180);
}

static void	copy_to_cell(t_game_data *gd, char **map)
{
	size_t	i;
	size_t	j;
	size_t	len;

	i = 0;
	gd->map2 = (t_cell **)x_malloc(sizeof(t_cell *) * gd->rows);
	while (i < gd->rows)
	{
		gd->map2[i] = x_malloc(sizeof(t_cell) * gd->cols);
		len = ft_strlen(map[i]);
		j = 0;
		while (j < len)
		{
			gd->map2[i][j].type = map[i][j];
			gd->map2[i][j].door_open = CLOSE;
			j++;
		}
		while (j < gd->cols)
		{
			gd->map2[i][j].type = ' ';
			gd->map2[i][j].door_open = CLOSE;
			j++;
		}
		i++;
	}
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
	gd->map_width = cols * TILE_SIZE;
	gd->map_height = rows * TILE_SIZE;
	gd->win_width = WINDOW_WIDTH;
	gd->win_height = WINDOW_HEIGHT;
	gd->ray = gd->win_width / WALL_STRIP_WIDTH;
	copy_to_cell(gd, gd->map);
}

void	init_mlx(t_game_data *data)
{
	int			win_x;
	int			win_y;
	t_img_data	*m;

	m = &data->map_img_data;
	data->mlx = mlx_init();
	if (!data->mlx)
		free_exit(data, INIT_ERROR);
	mlx_get_screen_size(data->mlx, &win_x, &win_y);
	if ((size_t)win_x < data->win_width || (size_t)win_y < data->win_height)
		free_exit(data, MAPSIZE_ERROR);
	data->win = mlx_new_window(data->mlx, data->win_width,
			data->win_height, TITLE);
	if (!data->win)
		free_exit(data, INIT_ERROR);
	m->ptr = mlx_new_image(data->mlx, data->win_width, data->win_height);
	if (!m->ptr)
		free_exit(data, INIT_ERROR);
	m->addr = (int *)mlx_get_data_addr(m->ptr, &m->bits_per_pixel,
			&m->line_lenght, &m->endian);
}

void	open_tex(t_game_data *data, t_img_data *img, char *path)
{
	img->ptr = mlx_xpm_file_to_image(data->mlx, path, &img->width, &img->height);
	if (!img->ptr || img->width != TILE_SIZE || img->height != TILE_SIZE)
		free_exit(data, "Failed to load image");
	img->addr = (int *)mlx_get_data_addr(img->ptr, &img->bits_per_pixel, &img->line_lenght, &img->endian);
	if (!img->addr)
		free_exit(data, INIT_ERROR);
}

void	open_all_tex(t_game_data *data, t_imgs *img)
{
	open_tex(data, &img->wall_north, data->tp.no_path);
	open_tex(data, &img->wall_south, data->tp.so_path);
	open_tex(data, &img->wall_east, data->tp.ea_path);
	open_tex(data, &img->wall_west, data->tp.we_path);
	open_tex(data, &img->door, DOOR_TEX_PATH);
}
