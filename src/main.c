#include "cub3d.h"

int	main(int ac, char **av)
{
	t_game_data	data;

	check_arg(ac, av);
	data.fov = malloc(sizeof(t_fov) * RAYS);
	dset_map(&data.map);
	dinit_map(&data);
	dinit_player();
	put_all_tile(&data);
	dloop_start(&data);
	return (0);
}
