#include "debug.h"

int	main(void)
{
	t_game_data	data;

	data.fov = malloc(sizeof(t_fov) * RAYS);
	dset_map(&data.map);
	dinit_map(&data);
	dinit_player();
	put_all_tile(&data);
	dloop_start(&data);
	return (0);
}
