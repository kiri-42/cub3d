/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cubfile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar  <tkirihar@student.42tokyo.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/26 15:27:00 by tkirihar          #+#    #+#             */
/*   Updated: 2022/07/26 15:27:00 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_cubfile(t_game_data *gd)
{
	int	i;

	i = 0;
	while (gd->cubfile[i] != NULL)
	{
		free(gd->cubfile[i]);
		i++;
	}
	free(gd->cubfile);
}
