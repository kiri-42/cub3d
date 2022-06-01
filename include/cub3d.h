#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "libft.h"
# include "mlx.h"

typedef struct s_game_data
{
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
}	t_game_data;

void	check_arg(int ac, char **av);
void	read_cubfile(t_game_data *gd, char *cubfile);
void	finish_error(char *error_message);


#endif
