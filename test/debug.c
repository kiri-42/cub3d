#include "debug.h"

void	print_map_data(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (i < ROWS)
	{
		j = 0;
		printf("{");
		while (j < COLS)
		{
			printf("%d", map[i][j]);
			if (j + 1 < COLS)
				printf(", ");
			j++;
		}
		printf("}\n");
		i++;
	}
	printf("\n");
}