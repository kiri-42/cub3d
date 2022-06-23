#include "cub3d.h"
#include "debug.h"

// int	main()
// {
// 	t_game_data	data;

// 	init_player();
// 	dinit_map(&data);
// 	draw_white_square(&data);
// 	draw_player(&data);
// 	set_map(&data.map);
// 	dloop_start(&data);
// 	return (0);
// }

int	main()
{
	t_game_data	data;

	init_player();
	dinit_map(&data);
	set_map(&data.map);
	draw_player(&data);
	// set_white_square();
	draw_map2(&data);
	dloop_start(&data);
	return (0);
}
