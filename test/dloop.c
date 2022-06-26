#include "debug.h"

int	dclose_window(void)
{
	exit(EXIT_SUCCESS);
}

int	dkey_hook(int keycode, t_game_data *data)
{
	(void)data;
	double moveStep;

	if (keycode == KEY_ESC)
		close_window();
	else if (keycode == KEY_W)
	{
		player.walkDirection = 1;
		moveStep = player.walkDirection * player.moveSpeed;
		printf("x:%f y:%f\n", player.x, player.y);
		printf("x':%f y':%f\n", player.x+cos(player.rotationAngle)*moveStep, player.y+sin(player.rotationAngle)*moveStep);
		player.x += cos(player.rotationAngle) * moveStep;
		player.y += sin(player.rotationAngle) * moveStep;
	}
	else if (keycode == KEY_A)
		player.turnDirection = -1;
	else if (keycode == KEY_S)
	{
		player.walkDirection = -1;
		moveStep = player.walkDirection * player.moveSpeed;
		printf("x:%f y:%f\n", player.x, player.y);
		printf("x':%f y':%f\n", player.x+cos(player.rotationAngle)*moveStep, player.y+sin(player.rotationAngle)*moveStep);
		player.x += cos(player.rotationAngle) * moveStep;
		player.y += sin(player.rotationAngle) * moveStep;
	}
	else if (keycode == KEY_D)
		player.turnDirection = 1;
	player.rotationAngle += player.turnDirection * player.rotationSpeed;
	player.turnDirection = 0;
	player.walkDirection = 0;
	return (0);
}

int	dloop_hook(t_game_data *data)
{
	put_all_tile(data);
	map.addr[TO_COORD(player.x, player.y)] = 0xFF0000;
	draw_line(map, player.x, player.y, player.x+cos(player.rotationAngle)*30, player.y+sin(player.rotationAngle)*30);
	mlx_put_image_to_window(data->mlx, data->win, map.img, 0, 0);
	return (0);
}

void	dloop_start(t_game_data *data)
{
	mlx_key_hook(data->win, dkey_hook, data);
	mlx_hook(data->win, 17, 0, dclose_window, NULL);
	mlx_loop_hook(data->mlx, dloop_hook, data);
	mlx_loop(data->mlx);
}
