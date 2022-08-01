/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coord.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar  <tkirihar@student.42tokyo.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 22:54:49 by tkirihar          #+#    #+#             */
/*   Updated: 2022/07/27 22:54:49 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	to_chr_index(int width, t_coord coord, double scale)
{
	return ((int)round(coord.y * scale) * width + (int)round(coord.x * scale));
}

t_position	divide_coord(t_coord coord, double denominator)
{
	t_position	p;

	p.x = (int)floor(coord.x / denominator);
	p.y = (int)floor(coord.y / denominator);
	return (p);
}

t_cell	*get_cell_addr(t_game_data *gd, t_cell **map, t_coord coord)
{
	int	x;
	int	y;

	x = (int)floor((coord.x) / TILE_SIZE);
	y = (int)floor((coord.y) / TILE_SIZE);
	if ((size_t)x >= gd->cols || (size_t)y >= gd->rows)
		return (NULL);
	return (&map[y][x]);
}

t_coord	floor_coord(t_coord coord)
{
	coord.x = floor(coord.x);
	coord.y = floor(coord.y);
	return (coord);
}
