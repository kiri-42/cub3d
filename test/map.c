#include "debug.h"
#include <string.h>
#include <math.h>

void	draw_map(t_game_data *data)
{
	int		*addr;
	int		bits_per_pixel;
	int		line_lenght;
	int		endian;
	int	i;

	i = 0;
	map = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	addr = (int *)mlx_get_data_addr(map, &bits_per_pixel, &line_lenght, &endian);
	while (i < WIDTH * HEIGHT)
	{
		addr[i] = 0xFFFFFF;
		i++;
	}
	mlx_put_image_to_window(data->mlx, data->win, map, 0, 0);
}
