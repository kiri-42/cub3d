#include "cub3d.h"

/* Function to check if a map file has a .ber extension */
static bool	is_ber_extension(char *map_file)
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
		finish_error("the number of arguments is different");
	if (!is_ber_extension(av[1]))
		finish_error("the map file could not be loaded");
}
