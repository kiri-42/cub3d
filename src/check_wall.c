#include "cub3d.h"

int	get_line_size(char **map)
{
	int	i;

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
	int	line_size;
	int	i;

	line_size = get_line_size(map);
	dup = (char **)x_malloc(sizeof(int) * (line_size + 1));
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
	int	i;

	i = 0;
	while (map[i] != NULL)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

bool	is_valid_position(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

void	get_position(char **map, char *c, int *x, int *y)
{
	int	i;
	int	j;

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
	*c = ' ';
	return ;
}

void	flood_fill(char **map, int x, int y, int max_y, char new_color)
{
	int	max_x;

	max_x = ft_strlen(map[y]);
	if (x < 0 || y < 0 || x >= max_x || y >= max_y)
		return ;
	if (map[y][x] == new_color)
		return ;
	if (!is_valid_position(map[y][x]))
	{
		if (map[y][x] == '1')
			return ;
		else
			exit_error(WALL_ERROR);
	}

	map[y][x] = new_color;

	flood_fill(map, x + 1, y, max_y, new_color);
	flood_fill(map, x - 1, y, max_y, new_color);
	flood_fill(map, x, y + 1, max_y, new_color);
	flood_fill(map, x, y - 1, max_y, new_color);
}

void	check_wall(t_game_data *gd)
{
	char	**map;
	char	c;
	int		x;
	int		y;
	int		max_y;

	map = dupmap(gd->map);
	max_y = get_line_size(map);
	while (true)
	{
		get_position(map, &c, &x, &y);
		if (c == ' ')
			break ;
		flood_fill(map, x, y, max_y, '#');
	}
}
