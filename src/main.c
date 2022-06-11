#include "cub3d.h"

// void	check_texture_path(t_game_data *gd)
// {
// 	(void)gd;
// 	printf("texture_path\n");
// }

void	init_texture_path_NULL(t_texture_path *tp)
{
	tp->no_path = NULL;
	tp->so_path = NULL;
	tp->we_path = NULL;
	tp->ea_path = NULL;
}

void	init_rgb(t_rgb *color)
{
	color->red = -1;
	color->green = -1;
	color->blue = -1;
}

void	init_game_data_NULL(t_game_data *gd)
{
	init_texture_path_NULL(&(gd->tp));
	init_rgb(&(gd->ceiling_color));
	init_rgb(&(gd->floor_color));
	gd->map = NULL;
}

int	main(int ac, char **av)
{
	t_game_data	gd;

	check_arg(ac, av);
	init_game_data_NULL(&gd);
	read_cubfile(&gd, av[1]);
	set_game_data(&gd);
	free_cubfile(&gd);
	// check_texture_path(&gd);
	check_map(&gd);
	// print_texture_path(&gd);
	return (0);
}
