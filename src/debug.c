#include "cub3d.h"

void	debug_set_map(char ***m)
{
	int	i;
	int	j;
	char map[11][15] = {
	{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '1'},
	{'1', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '1', '0', '1'},
	{'1', '1', '1', '1', '0', '0', '0', '0', '0', '0', '1', '0', '1', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '1', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '1', '1', '1', '1', '1', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '1', '1', '1', '1', '1', '0', '0', '0', '1', '1', '1', '1', '0', '1'},
	{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
	{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}
	};

	// char map[ROWS][COLS] = {
	// {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	// {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	// {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	// {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	// {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	// {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
	// {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	// {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	// {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	// {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	// {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	// };

	i = 0;
	*m = malloc(sizeof(char *) * (11 + 1));
	while (i < 11)
	{
		j = 0;
		(*m)[i] = malloc(sizeof(char) * 15);
		while (j < 15)
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
	while (map[i])
	{
		j = 0;
		printf("{");
		while (map[i][j])
		{
			printf("%c", map[i][j]);
			if (map[i][j + 1])
				printf(", ");
			j++;
		}
		printf("}\n");
		i++;
	}
	printf("\n");
}

void	debug_set_color(t_game_data *data)
{
	data->floor_color.red = 0;
	data->floor_color.green = 0;
	data->floor_color.blue = 0xFF;
	data->floor_color.code = 0x0000FF;
	data->ceiling_color.red = 0;
	data->ceiling_color.green = 0xFF;
	data->ceiling_color.blue = 0;
	data->ceiling_color.code = 0x00FF00;
}

void	debug_set_texpath(t_game_data *data)
{
	data->tp.no_path = ft_strdup("./texture/wall_north.xpm");
	data->tp.so_path = ft_strdup("./texture/wall_south.xpm");
	data->tp.ea_path = ft_strdup("./texture/wall_east.xpm");
	data->tp.we_path = ft_strdup("./texture/wall_west.xpm");
}

bool	open_tex(t_game_data *data, t_imgs *img)
{
	img->wall_north.ptr = mlx_xpm_file_to_image(data->mlx, data->tp.no_path, &img->wall_north.width, &img->wall_north.height);
	img->wall_north.addr = mlx_get_data_addr(img->wall_north.ptr, &img->wall_north.bits_per_pixel, &img->wall_north.line_lenght, &img->wall_north.endian);
	img->wall_south.ptr = mlx_xpm_file_to_image(data->mlx, data->tp.so_path, &img->wall_south.width, &img->wall_south.height);
	img->wall_south.addr = mlx_get_data_addr(img->wall_south.ptr, &img->wall_south.bits_per_pixel, &img->wall_south.line_lenght, &img->wall_south.endian);
	img->wall_east.ptr = mlx_xpm_file_to_image(data->mlx, data->tp.ea_path, &img->wall_east.width, &img->wall_east.height);
	img->wall_east.addr = mlx_get_data_addr(img->wall_east.ptr, &img->wall_east.bits_per_pixel, &img->wall_east.line_lenght, &img->wall_east.endian);
	img->wall_west.ptr = mlx_xpm_file_to_image(data->mlx, data->tp.we_path, &img->wall_west.width, &img->wall_west.height);
	img->wall_west.addr = mlx_get_data_addr(img->wall_west.ptr, &img->wall_west.bits_per_pixel, &img->wall_west.line_lenght, &img->wall_west.endian);
	return (true);
}
