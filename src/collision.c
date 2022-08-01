/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar  <tkirihar@student.42tokyo.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 08:59:52 by tkirihar          #+#    #+#             */
/*   Updated: 2022/07/28 08:59:52 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	get_minimap_tile(t_game_data *data, double x, double y)
{
	size_t	map_x;
	size_t	map_y;

	if (x < 0 || x > data->map_width || y < 0 || y > data->map_height)
		return (' ');
	map_x = floor(x / (TILE_SIZE * MINIMAP_SCALE));
	map_y = floor(y / (TILE_SIZE * MINIMAP_SCALE));
	if (map_x >= data->cols || map_y >= data->rows)
		return (' ');
	return (data->map2[map_y][map_x].type);
}
