/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_win.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkirihar  <tkirihar@student.42tokyo.>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 15:44:46 by tkirihar          #+#    #+#             */
/*   Updated: 2022/06/01 15:44:46 by tkirihar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */




#include "mlx.h"


void *mlx;
void *win1;
void *win2;



int gere_mouse(int x,int y,int button,void*toto)
{
  printf("Mouse event - new win\n");
  mlx_destroy_window(mlx,win1);
  win1 = mlx_new_window(mlx,random()%500,random()%500,"new win");
  mlx_mouse_hook(win1,gere_mouse,0);
}


int main()
{
  srandom(time(0));
  mlx = mlx_init();
  win1 = mlx_new_window(mlx,300,300,"win1");
  win2 = mlx_new_window(mlx,600,600,"win2");
  mlx_mouse_hook(win1,gere_mouse,0);
  mlx_mouse_hook(win2,gere_mouse,0);
  mlx_loop(mlx);
}
