/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar  <tkirihar@student.42tokyo.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:42:16 by tkirihar          #+#    #+#             */
/*   Updated: 2022/06/01 15:42:16 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	*u_s;
	unsigned char	u_c;
	size_t			len;

	u_s = (unsigned char *)s;
	u_c = (unsigned char)c;
	len = ft_strlen(s);
	while (len)
	{
		if (u_s[len] == u_c)
			break ;
		len--;
	}
	if (u_s[len] == u_c)
		return ((char *)&u_s[len]);
	return (NULL);
}
