#include "cub3d.h"

int	close_window(void)
{
	exit(EXIT_SUCCESS);
}

int	key_hook(int keycode, t_game_data *data)
{
	(void)data;
	if (keycode == KEY_ESC)
		close_window();
	return (0);
}
