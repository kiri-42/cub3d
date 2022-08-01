/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_int_wait_first_expose.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar  <tkirihar@student.42tokyo.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:44:46 by tkirihar          #+#    #+#             */
/*   Updated: 2022/06/01 15:44:46 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** mlx_int_wait_first_expose.c for minilibx in 
** 
** Made by olivier crouzet
** Login   <ol@epita.fr>
** 
** Started on  Tue Oct 17 09:26:45 2000 olivier crouzet
** Last update Fri Feb 23 17:27:10 2001 Charlie Root
*/



#include	"mlx_int.h"



int	mlx_int_wait_first_expose(t_xvar *xvar,Window win)
{
  XEvent	ev;

  XWindowEvent(xvar->display,win,ExposureMask,&ev);
  XPutBackEvent(xvar->display,&ev);
}
