#include "cub3d.h"
#include "debug.h"

int	dclose_window(void)
{
	exit(EXIT_SUCCESS);
}

void	to_draw_line(t_game_data *data)
{
	int		*addr;
	int		bits_per_pixel;
	int		line_lenght;
	int		endian;
	int	len;

	(void)data;
	addr = (int *)mlx_get_data_addr(map, &bits_per_pixel, &line_lenght, &endian);
	len = 100;
	if (player.y + len > HEIGHT)
		len = 0;
	draw_line(addr, player.x, player.y, player.x, player.y+len);
}

int	dkey_hook(int keycode, t_game_data *data)
{
	(void)data;
	if (keycode == KEY_ESC)
		close_window();
	else if (keycode == KEY_W)
		player.y--;
	else if (keycode == KEY_A)
		player.x--;
	else if (keycode == KEY_S)
		player.y++;
	else if (keycode == KEY_D)
		player.x++;
	draw_all(data);
	to_draw_line(data);
	mlx_put_image_to_window(data->mlx, data->win, map, 0, 0);
	mlx_put_image_to_window(data->mlx, data->win, player.img, player.x, player.y);
	return (0);
}

void	dloop_start(t_game_data *data)
{
	mlx_key_hook(data->win, dkey_hook, data);
	mlx_hook(data->win, 17, 0, dclose_window, NULL);
	mlx_loop(data->mlx);
}
