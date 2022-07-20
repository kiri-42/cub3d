#include "cub3d.h"

void	init_texture_path(t_texture_path *tp)
{
	tp->no_path = NULL;
	tp->so_path = NULL;
	tp->we_path = NULL;
	tp->ea_path = NULL;
}

void	init_rgb(t_rgb *color)
{
	color->red = -1;
	color->green = -1;
	color->blue = -1;
}

void	init_game_data(t_game_data *gd)
{
	ft_bzero(gd, sizeof(t_game_data));
	init_texture_path(&(gd->tp));
	init_rgb(&(gd->ceiling_color));
	init_rgb(&(gd->floor_color));
	gd->map = NULL;
}
