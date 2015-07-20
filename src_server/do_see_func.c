/*
** do_see_func.c for  in /home/frayss_c/tmp_zappy/Zappy/src_server
** 
** Made by Christophe Fraysse
** Login   <frayss_c@epitech.net>
** 
** Started on  Sun Jul  5 21:36:47 2015 Christophe Fraysse
** Last update Sun Jul  5 21:38:12 2015 Christophe Fraysse
*/

#include "server.h"

int	set_tmp_coord(int tmp, int length)
{
  while (tmp >= length)
    tmp -= length;
  while (tmp < 0)
    tmp += length;
  return (tmp);
}
