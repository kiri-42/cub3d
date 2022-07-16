#include "cub3d.h"

int	main(int ac, char **av)
{
	t_game_data	gd;

	// check_arg(ac, av);
	// init_game_data(&gd);
	// read_cubfile(&gd, av[1]);
	// set_game_data(&gd);
	// free_cubfile(&gd);
	// printf("%s %d\n", __FILE__, __LINE__);
	// check_game_data(&gd);
	// printf("%s %d\n", __FILE__, __LINE__);

	/* for debug */
	debug_set_color(&gd);
	debug_set_texpath(&gd);
	debug_set_map(&gd.map);

	gd.fov = malloc(sizeof(t_fov) * RAYS);	
	printf("%s %d", __FILE__, __LINE__);
	dinit_map(&gd);
	printf("%s %d", __FILE__, __LINE__);
	dinit_player();
	printf("%s %d\n", __FILE__, __LINE__);
	put_all_tile(&gd);
	printf("%s %d", __FILE__, __LINE__);
	dloop_start(&gd);
	return (0);
}
