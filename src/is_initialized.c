#include "cub3d.h"

void	is_initialized_rgb(t_rgb color)
{
	if (color.red == -1)
		exit_error("red is uninitialized");
	if (color.green == -1)
		exit_error("green is uninitialized");
	if (color.blue == -1)
		exit_error("blue is uninitialized");
}

void	is_initialized(t_game_data *gd)
{
	is_initialized_rgb(gd->ceiling_color);
	is_initialized_rgb(gd->floor_color);
	if (gd->map == NULL)
		exit_error("map is uninitialized");
}
