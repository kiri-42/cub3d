#include "cub3d.h"

int	main(int ac, char **av)
{
	t_game_data	gd;

	check_arg(ac, av);
	init_game_data(&gd);
	read_cubfile(&gd, av[1]);
	set_game_data(&gd);
	free_cubfile(&gd);
	check_game_data(&gd);
	// check_texture_path(&gd);
	// check_map(&gd);
	// print_texture_path(&gd);
	return (0);
}
