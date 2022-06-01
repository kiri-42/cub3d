#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdbool.h>
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
void	finish_error(char *error_message);


#endif
