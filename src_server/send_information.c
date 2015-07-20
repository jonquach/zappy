/*
** send_information.c for qsd in /home/quach_a/backupzappy/Zappy/src_server
** 
** Made by Jonathan Quach
** Login  <jonathan.quach@epitech.eu>
** 
** Started on  Sun Jul  5 20:58:46 2015 Jonathan Quach
** Last update Sun Jul  5 21:25:43 2015 Christophe Fraysse
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "server.h"
#include "protocol.h"

t_bool			send_information_to_graphic(t_server *s, int fd)
{
  gc_init(s, fd);
  return (true);
}

t_bool			send_information(t_server *s, int fd)
{
  int			i;
  t_user		*tmp;
  t_team		*tmp_team;
  char			msg[4096];

  i = 0;
  tmp = s->users;
  tmp_team = s->team;
  memset(msg, 0, 4096);
  while (tmp->fd != fd && tmp != NULL)
    tmp = tmp->next;
  while (tmp_team[i].name != NULL)
    {
      if (strcmp(tmp_team[i].name, tmp->team_name) == 0)
	{
	  sprintf(msg, "%d\n%d %d\n", tmp_team[i].nb,
		  s->option->width, s->option->height);
	  safe_write(fd, strlen(msg), msg);
	  return (true);
	}
      ++i;
    }
  return (false);
}
