/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_game_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar  <tkirihar@student.42tokyo.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 15:27:00 by tkirihar          #+#    #+#             */
/*   Updated: 2022/08/01 14:08:55 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_texture_path(t_texture_path tp)
{
	is_initialized_texture_path(tp);
	is_open_texture_path(tp);
}

void	check_rgb(t_rgb color)
{
	is_initialized_rgb(color);
	is_invalid_rgb(color);
}

void	check_map(t_game_data *gd)
{
	is_initialized_map(gd->map);
	check_N(gd->map);
	check_wall(gd);
}

void	check_game_data(t_game_data *gd)
{
	check_texture_path(gd->tp);
	check_rgb(gd->ceiling_color);
	check_rgb(gd->floor_color);
	check_map(gd);
}
