/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_int_set_win_event_mask.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar  <tkirihar@student.42tokyo.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:44:46 by tkirihar          #+#    #+#             */
/*   Updated: 2022/06/01 15:44:46 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** mlx_int_set_win_event_mask.c for MiniLibX in 
** 
** Made by Charlie Root
** Login   <ol@epitech.net>
** 
** Started on  Thu Aug  3 11:49:06 2000 Charlie Root
** Last update Fri Feb 23 17:07:42 2001 Charlie Root
*/


#include	"mlx_int.h"




int	mlx_int_set_win_event_mask(t_xvar *xvar)
{
  t_win_list	*win;
  int		mask;
  int		i;
  XSetWindowAttributes	xwa;

  win = xvar->win_list;
  while (win)
    {
      xwa.event_mask = 0;
      i = MLX_MAX_EVENT;
      while (i--)
	xwa.event_mask |= win->hooks[i].mask;
      XChangeWindowAttributes(xvar->display, win->window, CWEventMask, &xwa);
      win = win->next;
    }
}
