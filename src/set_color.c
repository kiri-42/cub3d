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

void	set_color_line(t_game_data *gd, char *line, char *prefix, t_can_read_color *crc)
{
	t_rgb	rgb;
	rgb = get_rgb(line);
	if (!ft_strncmp(prefix, "F ", 2) && crc->floor)
	{
		crc->floor = false;
		gd->floor_color.red = rgb.red;
		gd->floor_color.green = rgb.green;
		gd->floor_color.blue = rgb.blue;
	}
	else if (!ft_strncmp(prefix, "C ", 2) && crc->ceiling)
	{
		crc->ceiling = false;
		gd->ceiling_color.red = rgb.red;
		gd->ceiling_color.green = rgb.green;
		gd->ceiling_color.blue = rgb.blue;
	}
	else
		exit_error(CUB_FORMAT_ERROR);
}

void	set_color(t_game_data *gd, size_t *line_i)
{
	size_t	start_i;
	char	*prefix;
	t_can_read_color	crc;

	crc.floor = true;
	crc.ceiling = true;
	start_i = *line_i;
	while (gd->cubfile[*line_i] != NULL && *line_i < start_i + 2)
	{
		prefix = ft_substr(gd->cubfile[*line_i], 0, PREFIX_SIZE);
		if (is_color_line(prefix))
			set_color_line(gd, gd->cubfile[*line_i], prefix, &crc);
		else
			exit_error(CUB_FORMAT_ERROR);
		(*line_i)++;
		free(prefix);
	}
	if (gd->cubfile[*line_i] == NULL)
		exit_error(CUB_FORMAT_ERROR);
	(*line_i)--;
}
