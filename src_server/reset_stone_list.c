/*
** reset_stone_list.c for qsd in /home/quach_a/backupzappy/Zappy/src_server
** 
** Made by Jonathan Quach
** Login  <jonathan.quach@epitech.eu>
** 
** Started on  Sun Jul  5 20:58:45 2015 Jonathan Quach
** Last update Sun Jul  5 20:58:45 2015 Jonathan Quach
*/

#include "server.h"

void	reset_stone_list(t_stone *list)
{
  int	i;

  i = 0;
  while (i < 6)
  {
    list[i].nb = 0;
    ++i;
  }
}
