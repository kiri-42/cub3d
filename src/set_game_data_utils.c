/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_game_data_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar  <tkirihar@student.42tokyo.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 15:27:00 by tkirihar          #+#    #+#             */
/*   Updated: 2022/07/26 16:52:10 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_path_line(char *str)
{
	return (!ft_strncmp(str, "NO", PREFIX_SIZE)
		|| !ft_strncmp(str, "SO", PREFIX_SIZE)
		|| !ft_strncmp(str, "WE", PREFIX_SIZE)
		|| !ft_strncmp(str, "EA", PREFIX_SIZE));
}

bool	is_color_line(char *str)
{
	return (!ft_strncmp(str, "F ", PREFIX_SIZE)
		|| !ft_strncmp(str, "C ", PREFIX_SIZE));
}
