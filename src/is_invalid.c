/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_invalid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar  <tkirihar@student.42tokyo.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 15:27:00 by tkirihar          #+#    #+#             */
/*   Updated: 2022/08/01 14:50:42 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	is_invalid_rgb(t_rgb color)
{
	if (!(0 <= color.red && color.red <= 255))
		exit_error(RGB_INVALID_ERROR);
	if (!(0 <= color.green && color.green <= 255))
		exit_error(RGB_INVALID_ERROR);
	if (!(0 <= color.blue && color.blue <= 255))
		exit_error(RGB_INVALID_ERROR);
}
