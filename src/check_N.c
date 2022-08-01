#include "cub3d.h"

void	check_N(char **map)
{
	int	i;
	int	j;
	int	count_N;

	count_N = 0;
	i = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] == 'N')
				count_N++;
			j++;
		}
		i++;
	}
	printf("%d\n", count_N);
	if (count_N != 1)
		exit_error(MAP_INVALID_ERROR);
}
