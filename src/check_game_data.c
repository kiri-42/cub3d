#include "cub3d.h"

void	check_texture_path(t_texture_path tp)
{
	printf("%s %d\n", __FILE__, __LINE__);
	is_initialized_texture_path(tp);
	printf("%s %d\n", __FILE__, __LINE__);
	is_open_texture_path(tp);
}

void	check_rgb(t_rgb color)
{
	is_initialized_rgb(color);
	is_invalid_rgb(color);
}

void	check_map(t_game_data *gd)
{
	is_initialized_map(gd->map);
	check_wall(gd);
}

void	check_game_data(t_game_data *gd)
{
	printf("%s %d\n", __FILE__, __LINE__);
	check_texture_path(gd->tp);
	printf("%s %d\n", __FILE__, __LINE__);
	check_rgb(gd->ceiling_color);
	check_rgb(gd->floor_color);
	printf("%s %d\n", __FILE__, __LINE__);
	check_map(gd);
}
