#include "cub3d.h"

void	print_cubfile(t_game_data *gd)
{
	size_t	i;

	i = 0;
	while (gd->cubfile[i] != NULL)
	{
		printf("%s\n", gd->cubfile[i]);
		i++;
	}
}
