#include "cub3d.h"

int	main(int ac, char **av)
{
	t_game_data	gd;

	check_arg(ac, av);
	init_game_data(&gd);
	gd.fov = malloc(sizeof(t_fov) * RAYS);
	dset_map(&gd.map);
	dinit_map(&gd);
	dinit_player();
	put_all_tile(&gd);
	dloop_start(&gd);
	return (0);
}
