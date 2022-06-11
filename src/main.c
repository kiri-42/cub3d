#include "cub3d.h"

int	main(int ac, char **av)
{
	t_game_data	gd;

	check_arg(ac, av);
	read_cubfile(&gd, av[1]);
	init_game_data(&gd);
	free_cubfile(&gd);
	check_map(&gd);
	// print_texture_path(&gd);
	return (0);
}
