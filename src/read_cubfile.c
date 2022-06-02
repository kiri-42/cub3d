#include "cub3d.h"

static void	set_texture_path(t_game_data *gd, int fd)
{
	char	*line;
	size_t	i;

	i = 0;
	*line = ""
	while ()
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (*line == "")
			continue;

		i++;
	}
}

void	read_cubfile(t_game_data *gd, char *cubfile)
{
	int	fd;

	fd = open(cubfile, O_RDONLY);
	if (fd == -1)
		exit_error("the file could not be opened");
	set_texture_path(gd, fd);
	close(fd);
}
