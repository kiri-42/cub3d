#include "cub3d.h"

// void	check_texture_path(t_game_data *gd)
// {
// 	(void)gd;
// 	printf("texture_path\n");
// }

void	is_initialized_texture_path(t_texture_path tp)
{
	if (tp.no_path == NULL)
		exit_error("no_path is uninitialized");
	if (tp.so_path == NULL)
		exit_error("so_path is uninitialized");
	if (tp.we_path == NULL)
		exit_error("we_path is uninitialized");
	if (tp.ea_path == NULL)
		exit_error("ea_path is uninitialized");
}

// pathの値が有効か確認する(未完成)
void	check_texture_path(t_texture_path tp)
{
	is_initialized_texture_path(tp);
}

void	is_initialized_rgb(t_rgb color)
{
	if (color.red == -1)
		exit_error("red is uninitialized");
	if (color.green == -1)
		exit_error("green is uninitialized");
	if (color.blue == -1)
		exit_error("blue is uninitialized");
}

// rgbの値が有効か確認する(未完成)
void	check_rgb(t_rgb color)
{
	is_initialized_rgb(color);
}

void	check_game_data(t_game_data *gd)
{
	is_initialized(gd);
	check_texture_path(gd->tp);
	check_rgb(gd->ceiling_color);
	check_rgb(gd->floor_color);
}

int	main(int ac, char **av)
{
	t_game_data	gd;

	check_arg(ac, av);
	init_game_data(&gd);
	read_cubfile(&gd, av[1]);
	set_game_data(&gd);
	free_cubfile(&gd);
	check_game_data(&gd);
	// check_texture_path(&gd);
	check_map(&gd);
	// print_texture_path(&gd);
	return (0);
}
