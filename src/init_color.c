#include "cub3d.h"

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

void	init_color_line(t_game_data *gd, char *line, char *prefix)
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

void	init_color(t_game_data *gd, size_t *line_i)
{
	size_t	start_i;
	char	*prefix;

	start_i = *line_i;
	while (gd->cubfile[*line_i] != NULL && *line_i < start_i + 2)
	{
		prefix = ft_substr(gd->cubfile[*line_i], 0, PREFIX_SIZE);
		if (is_color_line(prefix))
			init_color_line(gd, gd->cubfile[*line_i], prefix);
		else
			exit_error("color_lineではありません");
		(*line_i)++;
		free(prefix);
	}
	if (gd->cubfile[*line_i] == NULL)
		exit_error("color_lineが4つありません");
	(*line_i)--;
}
