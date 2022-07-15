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

// void	print_fov_data(t_fov fov)
// {
// 	printf("=========\n");
// 	printf("horz x:%f, horz y:%f\n", fov.h_wall_hit.x, fov.h_wall_hit.y);
// 	printf("vert x:%f, vert y:%f\n", fov.v_wall_hit.x, fov.v_wall_hit.y);
// 	printf("distance:%f\n", fov.distance);
// }

void	init_north_tex(t_game_data *data, t_imgs *img)
{
	img->wall_north.ptr = mlx_xpm_file_to_image(data->mlx, "./texture/wall_north.xpm", &img->wall_north.width, &img->wall_north.height);
	img->wall_north.addr = mlx_get_data_addr(img->wall_north.ptr, &img->wall_north.bits_per_pixel, &img->wall_north.line_lenght, &img->wall_north.endian);
}
