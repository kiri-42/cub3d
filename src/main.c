#include "cub3d.h"

void	init_game_data(t_game_data *gd)
{
	size_t	i;
	size_t	init_count;
	int		line_type;
	char	*prefix;

	i = 0;
	init_count = 0;
	while (gd->cubfile[i] != NULL)
	{
		if (init_count < 6)
		{
			prefix = ft_substr(gd->cubfile[i], 0, 2);
			if (prefix == NULL)
				exit_error(MALLOC_ERROR);
			if (ft_strncmp(prefix, "NO", 2))
			free(prefix);
		}
		i++;
		init_count++;
	}
}

int	main(int ac, char **av)
{
	t_game_data	gd;

	check_arg(ac, av);
	read_cubfile(&gd, av[1]);
	init_game_data(&gd);
	return (0);
}
