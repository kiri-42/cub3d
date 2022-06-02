#include "cub3d.h"

bool	is_path_line(char *str)
{
	return (!ft_strncmp(str, "NO", 2) || !ft_strncmp(str, "SO", 2) || !ft_strncmp(str, "WE", 2) || !ft_strncmp(str, "EA", 2));
}

char	*get_texture_path(char *line)
{
	size_t	len;
	char	*texture_path;

	len = ft_strlen(line);
	texture_path = ft_substr(line, 3, len - 4);
	return (texture_path);
}

void	init_texture_path(t_game_data *gd, char *line, char *prefix)
{
	char	*texture_path;

	texture_path = get_texture_path(line);
	if (ft_strncmp(prefix, "NO", 2))
		gd->tp.no_path = texture_path;
	else if (ft_strncmp(prefix, "SO", 2))
		gd->tp.so_path = texture_path;
	else if (ft_strncmp(prefix, "WE", 2))
		gd->tp.we_path = texture_path;
	else if (ft_strncmp(prefix, "EA", 2))
		gd->tp.ea_path = texture_path;
}

// size_t	get_map_start_i(char **file)
// {
// 	size_t	i;

// 	while (file[i] != NULL)
// 	{
// 		if ()
// 	}

// }

void	init_game_data(t_game_data *gd)
{
	size_t	i;
	// size_t	map_start_i;
	size_t	init_count;
	char	*prefix;

	i = 0;
	init_count = 0;
	// map_start_i = get_map_start_i(gd->cubfile);
	while (gd->cubfile[i] != NULL)
	{
		if (init_count < 6)
		{
			prefix = ft_substr(gd->cubfile[i], 0, 2);
			if (prefix == NULL)
				exit_error(MALLOC_ERROR);
			if (is_path_line(prefix))
			{
				printf("%s\n", gd->cubfile[i]);
				init_texture_path(gd, gd->cubfile[i], prefix);
			}
			free(prefix);
		}
		i++;
		init_count++;
	}
}

int	main(int ac, char **av)
{
	t_game_data	gd;

	check_arg(ac, av);
	read_cubfile(&gd, av[1]);
	init_game_data(&gd);
	return (0);
}
