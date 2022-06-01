#include "cub3d.h"

/* Function to output an error message and exit the program */
void	finish_error(char *error_message)
{
	ft_putendl_fd(error_message, STDERR_FILENO);
	exit(1);
}
