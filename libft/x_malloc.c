/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_malloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar  <tkirihar@student.42tokyo.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 21:17:19 by tkirihar          #+#    #+#             */
/*   Updated: 2022/07/14 21:17:19 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*x_malloc(size_t size)
{
	void	*content;

	content = malloc(size);
	if (content == NULL)
		exit_error(MALLOC_ERROR);
	return (content);
}
