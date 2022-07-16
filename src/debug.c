#include "cub3d.h"

void	dset_map(char ***m)
{
	int	i;
	int	j;
	// char map[ROWS][COLS] = {
	// {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	// {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
	// {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
	// {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
	// {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
	// {1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1},
	// {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	// {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	// {1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1},
	// {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	// {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	// };

	char map[ROWS][COLS] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	};

	i = 0;
	*m = malloc(sizeof(char *) * (ROWS + 1));
	while (i < ROWS)
	{
		j = 0;
		(*m)[i] = malloc(sizeof(char) * COLS);
		while (j < COLS)
		{
			(*m)[i][j] = map[i][j];
			j++;
		}
		i++;
	}
	(*m)[i] = NULL;
}

void	print_map_data(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (i < ROWS)
	{
		j = 0;
		printf("{");
		while (j < COLS)
		{
			printf("%d", map[i][j]);
			if (j + 1 < COLS)
				printf(", ");
			j++;
		}
		printf("}\n");
		i++;
	}
	printf("\n");
}

void	print_player_data(t_player_data player)
{
	printf("x:%f, y:%f, angle:%f\n", player.pos.x, player.pos.y, player.rotation_angle);
}

void	debug_set_texpath(t_game_data *data)
{
	data->tp.no_path = ft_strdup("./texture/wall_north.xpm");
	data->tp.so_path = ft_strdup("./texture/wall_south.xpm");
	data->tp.ea_path = ft_strdup("./texture/wall_east.xpm");
	data->tp.we_path = ft_strdup("./texture/wall_west.xpm");
}

void	open_tex(t_game_data *data, t_imgs *img)
{
	debug_set_texpath(data);

	img->wall_north.ptr = mlx_xpm_file_to_image(data->mlx, data->tp.no_path, &img->wall_north.width, &img->wall_north.height);
	img->wall_north.addr = mlx_get_data_addr(img->wall_north.ptr, &img->wall_north.bits_per_pixel, &img->wall_north.line_lenght, &img->wall_north.endian);
	img->wall_south.ptr = mlx_xpm_file_to_image(data->mlx, data->tp.so_path, &img->wall_south.width, &img->wall_south.height);
	img->wall_south.addr = mlx_get_data_addr(img->wall_south.ptr, &img->wall_south.bits_per_pixel, &img->wall_south.line_lenght, &img->wall_south.endian);
	img->wall_east.ptr = mlx_xpm_file_to_image(data->mlx, data->tp.ea_path, &img->wall_east.width, &img->wall_east.height);
	img->wall_east.addr = mlx_get_data_addr(img->wall_east.ptr, &img->wall_east.bits_per_pixel, &img->wall_east.line_lenght, &img->wall_east.endian);
	img->wall_west.ptr = mlx_xpm_file_to_image(data->mlx, data->tp.we_path, &img->wall_west.width, &img->wall_west.height);
	img->wall_west.addr = mlx_get_data_addr(img->wall_west.ptr, &img->wall_west.bits_per_pixel, &img->wall_west.line_lenght, &img->wall_west.endian);
}
