#include "cub3d.h"

// デバッグ用の関数
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
