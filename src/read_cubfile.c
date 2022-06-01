#include "cub3d.h"

void	read_cubfile(t_game_data *gd, char *cubfile)
{
	int		fd;

	fd = open(cubfile, O_RDONLY);
	if (fd == -1)
		finish_error("the file could not be opened");
	(void)gd;
	close(fd);
}
