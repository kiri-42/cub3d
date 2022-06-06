#include "cub3d.h"

bool	is_valid_edge(char **map, size_t i, size_t j)
{
	if (map[i][j] == ' ' || map[i][j] == '1')
		return (true);
	return (false);
}

void	check_top_and_bottom_edge(char **map, size_t i)
{
	size_t	j;

	j = 0;
	while (map[i][j] != '\0')
	{
		if (!is_valid_edge(map, i, j))
			exit_error("Error");
		j++;
	}
}

void	check_left_and_right_edge(char **map, size_t i)
{
	if (!is_valid_edge(map, i, 0) || !is_valid_edge(map, i, ft_strlen(map[i]) - 1))
		exit_error("Error");
}

void	check_edge(t_game_data *gd)
{
	size_t	i;

	i = 0;
	while (gd->map[i] != NULL)
	{
		if (i == 0 || gd->map[i + 1] == NULL)
		{
			check_top_and_bottom_edge(gd->map, i);
		}
		else
		{
			check_left_and_right_edge(gd->map, i);
		}
		i++;
	}
}

void	check_space_block()
{
	printf("[space]");
}

void	check_zero_block()
{
	printf("[zero]");
}

void	check_one_block()
{
	printf("[one]");
}

void	check_north_block()
{
	printf("[north]");
}

void	check_south_block()
{
	printf("[south]");
}

void	check_west_block()
{
	printf("[west]");
}

void	check_east_block()
{
	printf("[east]");
}

void	separate_block(t_game_data *gd, size_t i, size_t j)
{
	if (gd->map[i][j] == ' ')
		check_space_block();
	else if (gd->map[i][j] == '0')
		check_zero_block();
	else if (gd->map[i][j] == '1')
		check_one_block();
	else if (gd->map[i][j] == 'N')
		check_north_block();
	else if (gd->map[i][j] == 'S')
		check_south_block();
	else if (gd->map[i][j] == 'W')
		check_west_block();
	else if (gd->map[i][j] == 'E')
		check_east_block();
	else
		exit_error("Error");
}

void	check_block(t_game_data *gd)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (gd->map[i] != NULL)
	{
		j = 0;
		while (gd->map[i][j] != '\0')
		{
			separate_block(gd, i, j);
			j++;
		}
		i++;
	}
}

void	check_map(t_game_data *gd)
{
	check_block(gd);
	check_edge(gd);
}

int	main(int ac, char **av)
{
	t_game_data	gd;

	check_arg(ac, av);
	read_cubfile(&gd, av[1]);
	init_game_data(&gd);
	free_cubfile(&gd);
	check_map(&gd);
	// print_texture_path(&gd);
	return (0);
}
