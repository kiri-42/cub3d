#include "cub3d.h"

bool	is_wall(t_cell **map, t_position p)
{
	t_cell	m;

	m = map[p.y][p.x];
	return (m.type == MAP_WALL || (m.type == MAP_DOOR && m.door_open == CLOSE));
}

bool	is_reachable_diagonal(t_game_data *data, t_cell **map, t_position new, t_position player)
{
	t_position p;
	t_position p2;

	p = player;
	p2 = player;
	if (new.x < 0 || new.y < 0 || (size_t)new.x >= data->cols || (size_t)new.y >= data->rows)
		return (false);
	if (new.x > player.x && new.y > player.y) //斜め右下
	{
		p.x = player.x + 1;
		p2.y = player.y + 1;
	}
	else if (new.x > player.x && new.y < player.y) //斜め右上
	{
		p.x = player.x + 1;
		p2.y = player.y - 1;
	}
	else if (new.x < player.x && new.y < player.y) //斜め左上
	{
		p.x = player.x - 1;
		p2.y = player.y - 1;
	}
	else if (new.x < player.x && new.y < player.y) //斜め左下
	{
		p.x = player.x - 1;
		p2.y = player.y + 1;
	}
	if (is_wall(map, p) == true && is_wall(map, p2) == true)
		return (false);
	return (true);
}

bool	is_reachable(t_game_data *gd, t_cell **map, t_coord coord)
{
	t_position	player;
	t_position	new;

	player = divide_coord(gd->player.pos, TILE_SIZE);
	new = divide_coord(coord, TILE_SIZE);
	if (player.x == new.x && player.y == new.y)
		return (true);
	if ((size_t)new.x >= gd->cols || (size_t)new.y >= gd->rows)
		return (false);
	if (is_wall(map, new))
		return (false);
	if (!is_reachable_diagonal(gd, map, new, player))
		return (false);
	return (true);
}
