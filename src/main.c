#include "cub3d.h"

void	free_cubfile(t_game_data *gd)
{
	size_t	i;

	i = 0;
	while (gd->cubfile[i] != NULL)
	{
		free(gd->cubfile[i]);
		i++;
	}
	free(gd->cubfile);
}

int	main(int ac, char **av)
{
	t_game_data	gd;

	check_arg(ac, av);
	read_cubfile(&gd, av[1]);
	init_game_data(&gd);
	free_cubfile(&gd);
	// print_texture_path(&gd);
	return (0);
}
