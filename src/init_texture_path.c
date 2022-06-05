#include "cub3d.h"

char	*get_texture_path(char *line)
{
	size_t	len;
	char	*texture_path;

	len = ft_strlen(line);
	texture_path = ft_substr(line, PREFIX_SIZE + 1, len - PREFIX_SIZE + 1);
	return (texture_path);
}

void	init_texture_path_line(t_game_data *gd, char *line, char *prefix, t_can_read_texture *crt)
{
	char	*texture_path;

	texture_path = get_texture_path(line);
	if (!ft_strncmp(prefix, "NO", PREFIX_SIZE) && crt->north)
	{
		crt->north = false;
		gd->tp.no_path = texture_path;
		// printf("%s\n", gd->tp.no_path);
	}
	else if (!ft_strncmp(prefix, "SO", PREFIX_SIZE) && crt->south)
	{
		crt->south = false;
		gd->tp.so_path = texture_path;
		// printf("%s\n", gd->tp.so_path);
	}
	else if (!ft_strncmp(prefix, "WE", PREFIX_SIZE) && crt->west)
	{
		crt->west = false;
		gd->tp.we_path = texture_path;
		// printf("%s\n", gd->tp.we_path);
	}
	else if (!ft_strncmp(prefix, "EA", PREFIX_SIZE) && crt->east)
	{
		crt->east = false;
		gd->tp.ea_path = texture_path;
		// printf("%s\n", gd->tp.ea_path);
	}
	else
	{
		exit_error("Error");
	}
	// printf("init\n");
	// print_texture_path(gd);
	// printf("end\n");
}

void	init_texture_path(t_game_data *gd, size_t *line_i)
{
	size_t	start_i;
	char	*prefix;
	t_can_read_texture	crt;

	crt.north = true;
	crt.south = true;
	crt.west = true;
	crt.east = true;
	start_i = *line_i;
	while (gd->cubfile[*line_i] != NULL && *line_i < start_i + 4)
	{
		prefix = ft_substr(gd->cubfile[*line_i], 0, PREFIX_SIZE);
		if (is_path_line(prefix))
			init_texture_path_line(gd, gd->cubfile[*line_i], prefix, &crt);
		else
			exit_error("path_lineではありません");
		(*line_i)++;
		free(prefix);
	}
	if (gd->cubfile[*line_i] == NULL)
		exit_error("pathが4つありません");
	(*line_i)--;
}
