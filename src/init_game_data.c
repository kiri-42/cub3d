#include "cub3d.h"

bool	is_path_line(char *str)
{
	return (!ft_strncmp(str, "NO", PREFIX_SIZE) || !ft_strncmp(str, "SO", PREFIX_SIZE) || !ft_strncmp(str, "WE", PREFIX_SIZE) || !ft_strncmp(str, "EA", PREFIX_SIZE));
}

bool	is_color_line(char *str)
{
	return (!ft_strncmp(str, "F ", PREFIX_SIZE) || !ft_strncmp(str, "C ", PREFIX_SIZE));
}

bool	is_map_start_line(char *line)
{
	size_t	i;

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

size_t	get_map_start_i(char **file)
{
	size_t	i;

	i = 0;
	while (file[i] != NULL)
	{
		if (is_map_start_line(file[i]))
			return (i);
		i++;
	}
	exit_error("mapが見つからない");
	return (0);
}

char	**malloc_map(t_game_data *gd, size_t map_start_i)
{
	char	**map;

	map = (char **)x_malloc((gd->cubfile_linage - map_start_i + 1) * sizeof(char *));
	return (map);
}

void	init_game_data(t_game_data *gd)
{
	size_t	i;
	size_t	map_start_i;
	char	*prefix;

	i = 0;
	map_start_i = get_map_start_i(gd->cubfile);
	gd->map = malloc_map(gd, map_start_i);
	while (gd->cubfile[i] != NULL)
	{
		if (i < map_start_i)
		{
			prefix = ft_substr(gd->cubfile[i], 0, PREFIX_SIZE);
			if (prefix == NULL)
				exit_error(MALLOC_ERROR);
			if (is_path_line(prefix))
				init_texture_path(gd, gd->cubfile[i], prefix);
			else if (is_color_line(prefix))
				init_color(gd, gd->cubfile[i], prefix);
			else if (gd->cubfile[i][0] != '\0')
				exit_error("Error");
			free(prefix);
		}
		else
		{
			gd->map[i - map_start_i] = ft_strdup(gd->cubfile[i]);
		}
		i++;
	}
	gd->map[i - map_start_i] = NULL;
	print_color(gd);
	print_texture_path(gd);
	print_map(gd);
}
