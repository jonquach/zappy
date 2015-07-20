/*
** gc_egg.c for qsd in /home/quach_a/backupzappy/Zappy/src_server/graphical_client
** 
** Made by Jonathan Quach
** Login  <jonathan.quach@epitech.eu>
** 
** Started on  Sun Jul  5 20:59:26 2015 Jonathan Quach
** Last update Sun Jul  5 20:59:27 2015 Jonathan Quach
*/

#include <string.h>
#include <stdio.h>
#include "server.h"
#include "protocol.h"

void	gc_do_fork(t_user *gc_list, t_user *u, int fde)
{
  char	buffer[512];

  memset(buffer, '\0', 512);
  sprintf(buffer, NEW_EGG, fde, u->fd, u->x,
	  u->y);
  safe_write_to_clients(gc_list, buffer);
  memset(buffer, '\0', 512);
  sprintf(buffer, DO_FORK, u->fd);
  safe_write_to_clients(gc_list, buffer);
}

void	gc_egg_hatch(t_user *gc_list, int fde)
{
  char	buffer[512];

  memset(buffer, '\0', 512);
  sprintf(buffer, EGG_HATCH, fde);
  safe_write_to_clients(gc_list, buffer);
}

void	connect_player_to_egg(t_user *gc_list, int fde)
{
  char	buffer[512];

  memset(buffer, '\0', 512);
  sprintf(buffer, CONNECT_PLAYER_TO_EGG, fde);
  safe_write_to_clients(gc_list, buffer);
}

void	gc_egg_die(t_user *gc_list, int fde)
{
  char	buffer[512];

  memset(buffer, '\0', 512);
  sprintf(buffer, EGG_DIEDEDED, fde);
  safe_write_to_clients(gc_list, buffer);
}
