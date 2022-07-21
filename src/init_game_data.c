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

void	init_player_pos(t_game_data *gd)
{
	size_t	i;
	char	*n;

	i = 0;
	n = NULL;
	while (gd->map[i])
	{
		n=ft_strchr(gd->map[i], 'N');
		// printf("%s\n", gd->map[i]);
		if (n)
			break;
		i++;
	}
	printf("%ld\n", n - gd->map[i]);
	gd->player.pos.x = (n - gd->map[i]) * TILE_SIZE;
	gd->player.pos.y = i * TILE_SIZE;
}
