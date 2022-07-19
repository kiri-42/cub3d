#include "cub3d.h"

void	print_map_data(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (i < ROWS)
	{
		j = 0;
		printf("{");
		while (j < COLS)
		{
			printf("%d", map[i][j]);
			if (j + 1 < COLS)
				printf(", ");
			j++;
		}
		printf("}\n");
		i++;
	}
	printf("\n");
}

int	main(int ac, char **av)
{
	t_game_data	gd;

	check_arg(ac, av);
	init_game_data(&gd);
	read_cubfile(&gd, av[1]);
	set_game_data(&gd);
	free_cubfile(&gd);
	check_game_data(&gd);
	print_map_data(gd.map);

	gd.fov = malloc(sizeof(t_fov) * RAYS);
	printf("%s %d\n", __FILE__, __LINE__);
	// dset_map(&gd.map);
	// print_map_data(gd.map);
	dinit_map(&gd);
	dinit_player();
	printf("%s %d\n", __FILE__, __LINE__);
	put_all_tile(&gd);
	printf("print");
	printf("%s %d\n", __FILE__, __LINE__);
	dloop_start(&gd);
	return (0);
}
