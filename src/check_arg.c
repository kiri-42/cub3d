/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar  <tkirihar@student.42tokyo.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 13:19:39 by tkirihar          #+#    #+#             */
/*   Updated: 2022/08/01 13:19:39 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	is_cub_extension(char *map_file)
{
	char	*extension;

	extension = ft_strrchr(map_file, '.');
	if (!extension || ft_strncmp(extension, ".cub", 5))
		return (false);
	return (true);
}

void	check_arg(int ac, char **av)
{
	if (ac != 2)
		exit_error(ARG_ERROR);
	if (!is_cub_extension(av[1]))
		exit_error(CUB_EXTENSION_ERROR);
}
