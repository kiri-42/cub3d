#include "cub3d.h"

void	is_open_path(char *path)
{
	int fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		exit_error("not open");
	close(fd);
}

void	is_open(t_texture_path tp)
{
	is_open_path(tp.no_path);
	is_open_path(tp.so_path);
	is_open_path(tp.we_path);
	is_open_path(tp.ea_path);
}

// pathの値が有効か確認する(未完成)
void	check_texture_path(t_texture_path tp)
{
	is_initialized_texture_path(tp);
	is_open(tp);
}

// rgbの値が有効か確認する(未完成)
void	check_rgb(t_rgb color)
{
	is_initialized_rgb(color);
	is_invalid_rgb(color);
}

// rgbの値が有効か確認する(未完成かも)
void	check_map(t_game_data *gd)
{
	is_initialized_map(gd->map);
	check_wall(gd);
}

void	check_game_data(t_game_data *gd)
{
	check_texture_path(gd->tp);
	check_rgb(gd->ceiling_color);
	check_rgb(gd->floor_color);
	check_map(gd);
}
