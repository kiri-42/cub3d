#include "cub3d.h"

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
