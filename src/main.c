#include "cub3d.h"

int	main(int ac, char **av)
{
	t_game_data	gd;

	(void)ac;
	(void)av;
	ft_bzero(&gd, sizeof(t_game_data));
	// check_arg(ac, av);
	// init_game_data(&gd);
	// read_cubfile(&gd, av[1]);
	// set_game_data(&gd);
	// free_cubfile(&gd);
	// printf("%s %d\n", __FILE__, __LINE__);
	// check_game_data(&gd);
	// printf("%s %d\n", __FILE__, __LINE__);

	/* ↓ for debug ↓ */
	debug_set_color(&gd);
	debug_set_texpath(&gd);
	debug_set_map(&gd.map);
	/* ↑ for debug ↑ */

	set_map_data(&gd);
	init_player_param(&gd);
	gd.fov = malloc(sizeof(t_fov) * gd.ray);
	init_mlx(&gd);
	open_tex(&gd, &gd.imgs);
	loop_start(&gd);
	return (0);
}
