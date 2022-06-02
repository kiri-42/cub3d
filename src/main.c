#include "cub3d.h"

int	main(int ac, char **av)
{
	t_game_data data;

	// check_arg(ac, av);
	(void)ac;
	(void)av;
	init_map(&data);
	loop_start(&data);
	return (0);
}
