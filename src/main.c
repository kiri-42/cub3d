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

// void	check_space_block(t_game_data *gd, size_t i, size_t j)
// {
// 	int	x;
// 	int	y;

// 	x = -1;
// 	y = -1;
// 	while (x <= 1)
// 	{
// 		if (i + x < 0)
// 		{
// 			x++;
// 			continue;
// 		}
// 		while (y <= 1)
// 		{

// 			if (!(gd->map[i + x][j + y] == ' ' || gd->map[i + x][j + y] == '1'))
// 				exit_error("Error")
// 			y++;
// 		}
// 		x++;
// 	}

// 	printf("[space]");
// }

// void	check_zero_block(t_game_data *gd, size_t i, size_t j)
// {
// 	printf("[zero]");
// }

// void	check_one_block(t_game_data *gd, size_t i, size_t j)
// {
// 	printf("[one]");
// }

// void	check_north_block(t_game_data *gd, size_t i, size_t j)
// {
// 	printf("[north]");
// }

// void	check_south_block(t_game_data *gd, size_t i, size_t j)
// {
// 	printf("[south]");
// }

// void	check_west_block(t_game_data *gd, size_t i, size_t j)
// {
// 	printf("[west]");
// }

// void	check_east_block(t_game_data *gd, size_t i, size_t j)
// {
// 	printf("[east]");
// }

// void	separate_block(t_game_data *gd, size_t i, size_t j)
// {
// 	if (gd->map[i][j] == ' ')
// 		check_space_block(gd, i, j);
// 	else if (gd->map[i][j] == '0')
// 		check_zero_block();
// 	else if (gd->map[i][j] == '1')
// 		check_one_block();
// 	else if (gd->map[i][j] == 'N')
// 		check_north_block();
// 	else if (gd->map[i][j] == 'S')
// 		check_south_block();
// 	else if (gd->map[i][j] == 'W')
// 		check_west_block();
// 	else if (gd->map[i][j] == 'E')
// 		check_east_block();
// 	else
// 		exit_error("非対応の文字です");
// }

// void	check_block(t_game_data *gd)
// {
// 	size_t	i;
// 	size_t	j;

// 	i = 0;
// 	while (gd->map[i] != NULL)
// 	{
// 		j = 0;
// 		while (gd->map[i][j] != '\0')
// 		{
// 			separate_block(gd, i, j);
// 			j++;
// 		}
// 		i++;
// 	}
// }

size_t	get_line_size(char **map)
{
	size_t	i;

	i = 0;
	while (map[i] != NULL)
	{
		i++;
	}
	return (i);
}

char **dupmap(char **map)
{
	char	**dup;
	size_t	line_size;
	size_t	i;

	line_size = get_line_size(map);
	dup = (char **)x_malloc(sizeof(size_t) * (line_size + 1));
	i = 0;
	while (i < line_size)
	{
		dup[i] = ft_strdup(map[i]);
		i++;
	}
	dup[i] = NULL;
	return (dup);
}

void	free_map(char **map)
{
	size_t	i;

	i = 0;
	while (map[i] != NULL)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

// void	flood_fill(char **map, size_t x, size_t y, char current_color, char new_color)
// {

// }

bool	is_valid_position(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

void	get_position(char **map, char *c, size_t *x, size_t *y)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (is_valid_position(map[i][j]))
			{
				*c = map[i][j];
				*x = j;
				*y = i;
				return ;
			}
			j++;
		}
		i++;
	}

}

void	check_wall(t_game_data *gd)
{
	char	**map;
	char	c;
	size_t	x;
	size_t	y;

	map = dupmap(gd->map);
	get_position(map, &c, &x, &y);
	printf("%c %zu, %zu\n", c, x, y);
	// flood_fill();
	free_map(map);
}

void	check_map(t_game_data *gd)
{
	// check_block(gd);
	check_edge(gd);
	check_wall(gd);
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
