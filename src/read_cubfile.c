#include "cub3d.h"

static size_t	count_line(char *file_name)
{
	char	*line;
	int		fd;
	size_t	line_size;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		exit_error("The file could not be opened");
	line_size = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		free(line);
		line_size++;
	}
	close(fd);
	return (line_size);
}

static char	**malloc_cubfile(char *cubfile_name)
{
	char	**cubfile;
	size_t	line_size;

	line_size = count_line(cubfile_name);
	cubfile = (char **)x_malloc((line_size + 1) * sizeof(char *));
	return (cubfile);
}

void	read_cubfile(t_game_data *gd, char *cubfile_name)
{
	int		fd;
	size_t	i;
	char	*line;

	gd->cubfile = malloc_cubfile(cubfile_name);
	fd = open(cubfile_name, O_RDONLY);
	if (fd == -1)
		exit_error("the file could not be opened");
	i = 0;
	while (true)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		gd->cubfile[i] = line;
		i++;
	}
	gd->cubfile[i] = NULL;
	close(fd);
}
