#include "cub3d.h"

/* Function to check if a map file has a .cub extension */
static bool	is_cub_extension(char *map_file)
{
	char	*extension;

	extension = ft_strrchr(map_file, '.');
	if (!extension || ft_strncmp(extension, ".cub", 4))
		return (false);
	return (true);
}

/* Function to check if command line arguments are in the correct format */
void	check_arg(int ac, char **av)
{
	if (ac != 2)
		exit_error(ARG_ERROR);
	if (!is_cub_extension(av[1]))
		exit_error(EXTENSION_ERROR);
}
