#include "cub3d.h"

void	print_cubfile(t_game_data *gd)
{
	size_t	i;

	i = 0;
	while (gd->cubfile[i] != NULL)
	{
		printf("%s\n", gd->cubfile[i]);
		i++;
	}
}

void	print_texture_path(t_game_data *gd)
{
	printf("no: %s\n", gd->tp.no_path);
	printf("so: %s\n", gd->tp.so_path);
	printf("ea: %s\n", gd->tp.ea_path);
	printf("we: %s\n", gd->tp.we_path);
}

void	print_color(t_game_data *gd)
{
	printf("<floor> r:%d g:%d b:%d\n", gd->floor_color.red, gd->floor_color.green, gd->floor_color.blue);
	printf("<ceiling> r:%d g:%d b:%d\n", gd->ceiling_color.red, gd->ceiling_color.green, gd->ceiling_color.blue);
}
