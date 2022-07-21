#include "cub3d.h"

int	main(int ac, char **av)
{
	t_game_data	gd;

	// (void)ac;
	// (void)av;
	/* input and check */
	check_arg(ac, av);
	init_game_data(&gd);
	read_cubfile(&gd, av[1]);
	set_game_data(&gd);
	// debug_print_cubfile(&gd);
	free_cubfile(&gd);
	// printf("%s %d\n", __FILE__, __LINE__);
	check_game_data(&gd);
	// printf("%s %d\n", __FILE__, __LINE__);


	// debug_set_color(&gd);
	// debug_set_map(&gd.map);
	// debug_set_texpath(&gd);
	gd.ceiling_color.code = (gd.ceiling_color.red << 16 | gd.ceiling_color.green << 8 | gd.ceiling_color.blue);
	gd.floor_color.code = (gd.floor_color.red << 16 | gd.floor_color.green << 8 | gd.floor_color.blue);
	set_map_data(&gd);
	printf("%s %d\n", __FILE__, __LINE__);
	init_player_param(&gd);
	printf("%s %d\n", __FILE__, __LINE__);
	gd.fov = malloc(sizeof(t_fov) * gd.ray);
	printf("%s %d\n", __FILE__, __LINE__);
	init_mlx(&gd);
	printf("%s %d\n", __FILE__, __LINE__);
	open_tex(&gd, &gd.imgs);
	printf("%s %d\n", __FILE__, __LINE__);
	loop_start(&gd);
	printf("%s %d\n", __FILE__, __LINE__);
	free_all(&gd);
	return (0);
}
