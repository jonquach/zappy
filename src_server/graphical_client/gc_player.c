/*
** gc_player.c for qsd in /home/quach_a/backupzappy/Zappy/src_server/graphical_client
** 
** Made by Jonathan Quach
** Login  <jonathan.quach@epitech.eu>
** 
** Started on  Sun Jul  5 20:59:34 2015 Jonathan Quach
** Last update Sun Jul  5 22:07:19 2015 Christophe Fraysse
*/

#include <string.h>
#include <stdio.h>
#include "server.h"
#include "protocol.h"

void		connect_new_player(t_user *gc_list, t_user *u, int fd)
{
  char		buffer[512];

  memset(buffer, '\0', 512);
  sprintf(buffer, NEW_PLAYER, u->fd, u->x, u->y, u->direction, u->level,
	  u->team_name);
  if (fd == -1)
    safe_write_to_clients(gc_list, buffer);
  else
    safe_write(fd, strlen(buffer), buffer);
}

void		update_player_pos(t_user *gc_list, t_user *u)
{
  char		buffer[512];

  memset(buffer, '\0', 512);
  printf("update player pos fd %d x %d y %d direction %d\n", u->fd,
	 u->x, u->y, u->direction);
  sprintf(buffer, PLAYER_POS, u->fd, u->x, u->y, u->direction);
  safe_write_to_clients(gc_list, buffer);
}

void		update_player_level(t_server *s, int x, int y, int level)
{
  char		buffer[512];
  t_user	*tmp;

  tmp = s->map[y * s->option->width + x].user_list;
  while (tmp != NULL)
    {
      if (tmp->level == level && x == tmp->x_incantation &&
	  y == tmp->y_incantation)
	{
	  memset(buffer, '\0', 512);
	  sprintf(buffer, PLAYER_LEVEL, tmp->fd, tmp->level);
	  safe_write_to_clients(s->gc_list, buffer);
	}
      tmp = tmp->next;
    }
}
