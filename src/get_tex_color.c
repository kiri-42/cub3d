#include "cub3d.h"

static t_rgb	get_rgb(int color)
{
	t_rgb	rgb;

	rgb.red = color >> 16;
	rgb.green = color >> 8 & 0xFF;
	rgb.blue = color & 0xFF;
	return (rgb);
}

static int	darken_color(int color, double distance)
{
	t_rgb	rgb;
	double	dark;

	rgb = get_rgb(color);
	dark = (200 / distance);
	if (dark > 1)
		dark = 1;
	rgb.red *= dark;
	rgb.green *= dark;
	rgb.blue *= dark;
	if (rgb.red > 0xFF)
		rgb.red = 0xFF;
	if (rgb.green > 0xFF)
		rgb.green = 0xFF;
	if (rgb.blue > 0xFF)
		rgb.blue = 0xFF;
	if (rgb.red < 0)
		rgb.red = 0;
	if (rgb.green < 0)
		rgb.green = 0;
	if (rgb.blue < 0)
		rgb.blue = 0;
	return (rgb.red << 16 | rgb.green << 8 | rgb.blue);
}

static t_position	get_tex_offset(t_fov *fov, int y)
{
	t_position	tex_offset;

	if (fov->was_hit_vert == true)
		tex_offset.x = (int)floor(fov->wall_hit.y) % TILE_SIZE;
	else
		tex_offset.x = (int)floor(fov->wall_hit.x) % TILE_SIZE;
	tex_offset.y = y * ((double)(TILE_SIZE) / fov->wall_strip_height);
	return (tex_offset);
}

int	get_tex_color(t_game_data *data, t_fov *fov, int y)
{
	t_position	p;
	int			color;

	p = get_tex_offset(fov, y);
	color = 0;
	if (fov->is_door)
		color = data->imgs.door.addr[p.y * TILE_SIZE + p.x];
	else
	{
		if (fov->d.up == true && fov->was_hit_vert == false)
			color = data->imgs.wall_north.addr[p.y * TILE_SIZE + p.x];
		else if (fov->d.right == true && fov->was_hit_vert == true)
			color = data->imgs.wall_east.addr[p.y * TILE_SIZE + p.x];
		else if (fov->d.left == true && fov->was_hit_vert == true)
			color = data->imgs.wall_west.addr[p.y * TILE_SIZE \
			+ (TILE_SIZE - 1 - p.x)];
		else if (fov->d.down == true && fov->was_hit_vert == false)
			color = data->imgs.wall_south.addr[p.y * TILE_SIZE \
			+ (TILE_SIZE - 1 - p.x)];
		else
			color = 0;
	}
	color = darken_color(color, fov->distance);
	return (color);
}
