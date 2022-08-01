/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_N.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar  <tkirihar@student.42tokyo.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 14:53:39 by tkirihar          #+#    #+#             */
/*   Updated: 2022/08/01 14:53:39 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_N(char **map)
{
	int	i;
	int	j;
	int	count_N;

	count_N = 0;
	i = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (map[i][j] == 'N' || map[i][j] == 'E' \
			|| map[i][j] == 'W' || map[i][j] == 'S')
				count_N++;
			j++;
		}
		i++;
	}
	if (count_N != 1)
		exit_error(MAP_INVALID_ERROR);
}
