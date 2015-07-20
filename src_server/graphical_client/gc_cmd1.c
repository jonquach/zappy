/*
** gc_cmd1.c for qsd in /home/quach_a/backupzappy/Zappy/src_server/graphical_client
** 
** Made by Jonathan Quach
** Login  <jonathan.quach@epitech.eu>
** 
** Started on  Sun Jul  5 20:59:21 2015 Jonathan Quach
** Last update Sun Jul  5 20:59:22 2015 Jonathan Quach
*/

#include <string.h>
#include <stdio.h>
#include "server.h"
#include "protocol.h"

void		gc_do_inventory(t_user *gc_list, t_user *u)
{
  char		buffer[512];

  memset(buffer, '\0', 512);
  sprintf(buffer, DO_INVENTORY, u->fd, u->x, u->y, u->stone_list[0].nb,
	  u->stone_list[1].nb, u->stone_list[2].nb, u->stone_list[3].nb,
	  u->stone_list[4].nb, u->stone_list[5].nb, u->stone_list[6].nb);
  safe_write_to_clients(gc_list, buffer);
}

void		gc_do_kick(t_user *gc_list, t_user *u)
{
  char		buffer[512];

  memset(buffer, '\0', 512);
  sprintf(buffer, DO_KICK, u->fd);
  safe_write_to_clients(gc_list, buffer);
}

void		gc_do_broadcast(t_user *gc_list, t_user *u, char *msg)
{
  char		buffer[512];

  memset(buffer, '\0', 512);
  sprintf(buffer, DO_BROADCAST, u->fd, msg);
  safe_write_to_clients(gc_list, buffer);
}

void		gc_do_incantation(t_server *s, int x, int y, int level)
{
  char		buffer[512];
  t_user	*tmp;

  tmp = s->users;
  while (tmp != NULL)
    {
      if (tmp->x == x && tmp->y == y && tmp->level == level)
	{
	  memset(buffer, '\0', 512);
	  sprintf(buffer, DO_INCANTATION, x, y, level, tmp->fd);
	  safe_write_to_clients(s->gc_list, buffer);
	}
      tmp = tmp->next;
    }
}

void		gc_end_incantation(t_user *gc_list, int x, int y, char *result)
{
  char		buffer[512];

  memset(buffer, '\0', 512);
  sprintf(buffer, END_INCANTATION, x, y, result);
  safe_write_to_clients(gc_list, buffer);
}
