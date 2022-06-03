#include "cub3d.h"

bool	is_color_line(char *str)
{
	return (!ft_strncmp(str, "F ", PREFIX_SIZE) || !ft_strncmp(str, "C ", PREFIX_SIZE));
}

bool	is_three_elem(char	**rgb)
{
	size_t	i;

	if (rgb == NULL)
		return (false);
	i = 0;
	while (rgb[i] != NULL)
	{
		i++;
	}
	if (i == 3)
		return (true);
	return (false);
}

t_rgb	get_rgb(char *line)
{
	size_t	len;
	t_rgb	rgb;
	char	*str_rgb;
	char	**split_rgb;

	len = ft_strlen(line);
	str_rgb = ft_substr(line, PREFIX_SIZE, len - PREFIX_SIZE);
	split_rgb = ft_split(str_rgb, ',');
	if (!is_three_elem(split_rgb))
		exit_error("Error");
	rgb.red = ft_atoi(split_rgb[0]);
	rgb.green = ft_atoi(split_rgb[1]);
	rgb.blue = ft_atoi(split_rgb[2]);
	free(split_rgb);
	free(str_rgb);
	return (rgb);
}

void	init_color(t_game_data *gd, char *line, char *prefix)
{
	t_rgb	rgb;

	// printf("init_color: %s\n", line);
	rgb = get_rgb(line);
	if (!ft_strncmp(prefix, "F ", 2))
	{
		gd->floor_color.red = rgb.red;
		gd->floor_color.green = rgb.green;
		gd->floor_color.blue = rgb.blue;
		// printf("%d %d %d\n", gd->floor_color.red, gd->floor_color.green, gd->floor_color.blue);
	}
	else if (!ft_strncmp(prefix, "C ", 2))
	{
		gd->ceiling_color.red = rgb.red;
		gd->ceiling_color.green = rgb.green;
		gd->ceiling_color.blue = rgb.blue;
		// printf("%d %d %d\n", gd->ceiling_color.red, gd->ceiling_color.green, gd->ceiling_color.blue);
	}
}


bool	is_path_line(char *str)
{
	return (!ft_strncmp(str, "NO", PREFIX_SIZE) || !ft_strncmp(str, "SO", PREFIX_SIZE) || !ft_strncmp(str, "WE", PREFIX_SIZE) || !ft_strncmp(str, "EA", PREFIX_SIZE));
}

char	*get_texture_path(char *line)
{
	size_t	len;
	char	*texture_path;

	len = ft_strlen(line);
	texture_path = ft_substr(line, PREFIX_SIZE + 1, len - PREFIX_SIZE + 1);
	return (texture_path);
}

void	init_texture_path(t_game_data *gd, char *line, char *prefix)
{
	char	*texture_path;

	texture_path = get_texture_path(line);
	if (!ft_strncmp(prefix, "NO", PREFIX_SIZE))
	{
		gd->tp.no_path = texture_path;
		// printf("%s\n", gd->tp.no_path);
	}
	else if (!ft_strncmp(prefix, "SO", PREFIX_SIZE))
	{
		gd->tp.so_path = texture_path;
		// printf("%s\n", gd->tp.so_path);
	}
	else if (!ft_strncmp(prefix, "WE", PREFIX_SIZE))
	{
		gd->tp.we_path = texture_path;
		// printf("%s\n", gd->tp.we_path);
	}
	else if (!ft_strncmp(prefix, "EA", PREFIX_SIZE))
	{
		gd->tp.ea_path = texture_path;
		// printf("%s\n", gd->tp.ea_path);
	}
	// printf("init\n");
	// print_texture_path(gd);
	// printf("end\n");
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
			if (is_color_line(prefix))
				init_color(gd, gd->cubfile[i], prefix);
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

int	main(int ac, char **av)
{
	t_game_data	gd;

	check_arg(ac, av);
	read_cubfile(&gd, av[1]);
	init_game_data(&gd);
	// print_texture_path(&gd);
	return (0);
}
