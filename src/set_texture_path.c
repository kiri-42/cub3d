/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_texture_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisoya <tisoya@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 15:27:00 by tkirihar          #+#    #+#             */
/*   Updated: 2022/08/01 16:06:12 by tisoya           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*get_texture_path(char *line)
{
	size_t	len;
	char	*texture_path;

	len = ft_strlen(line);
	texture_path = ft_substr(line, PREFIX_SIZE, len - PREFIX_SIZE);
	return (texture_path);
}
