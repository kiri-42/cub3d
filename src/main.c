#include "cub3d.h"

int	main(int ac, char **av)
{
	t_game_data	gd;

	check_arg(ac, av);
	read_cubfile(&gd, av[1]);
	print_cubfile(&gd);
	return (0);
}
