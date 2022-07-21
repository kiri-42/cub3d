#include "cub3d.h"

bool	is_map_start_line(char *line)
{
	int	i;

	if (line[0] == '\0')
		return (false);
	i = 0;
	while (line[i] != '\0')
	{
		if (!ft_strchr(" 1", line[i]))
			return (false);
		i++;
	}
	return (true);
}

int	get_map_start(char **file)
{
	int	i;

	i = 0;
	while (file[i] != NULL)
	{
		if (is_map_start_line(file[i]))
			return (i);
		i++;
	}
	exit_error(CUB_FORMAT_ERROR);
	return (0);
}

char	**malloc_map(t_game_data *gd, int map_start)
{
	char	**map;

	map = (char **)ft_calloc((gd->cubfile_linage - map_start + 1)
			* sizeof(char *), 1);
	return (map);
}

void	set_game_data(t_game_data *gd)
{
	int		i;
	int		map_start;
	char	*prefix;

	i = 0;
	map_start = get_map_start(gd->cubfile);
	gd->map = malloc_map(gd, map_start);
	while (gd->cubfile[i] != NULL)
	{
		if (i < map_start)
		{
			prefix = ft_substr(gd->cubfile[i], 0, PREFIX_SIZE);
			if (prefix == NULL)
				exit_error(MALLOC_ERROR);
			if (is_path_line(prefix))
				set_texture_path(gd, &i);
			else if (is_color_line(prefix))
				set_color(gd, &i);
			else if (gd->cubfile[i][0] != '\0' || i == 0)
				exit_error(CUB_FORMAT_ERROR);
			free(prefix);
		}
		else
		{
			gd->map[i - map_start] = ft_strdup(gd->cubfile[i]);
		}
		i++;
	}
	gd->map[i - map_start] = NULL;
}
