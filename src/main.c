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

int	main(int ac, char **av)
{
	t_game_data	gd;

	check_arg(ac, av);
	read_cubfile(&gd, av[1]);
	print_cubfile(&gd);
	return (0);
}
