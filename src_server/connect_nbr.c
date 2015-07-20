/*
** connect_nbr.c for qsd in /home/quach_a/backupzappy/Zappy/src_server
** 
** Made by Jonathan Quach
** Login  <jonathan.quach@epitech.eu>
** 
** Started on  Sun Jul  5 20:58:16 2015 Jonathan Quach
** Last update Sun Jul  5 20:58:16 2015 Jonathan Quach
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "server.h"

t_bool		do_connect(t_server *s, t_user *user, char *buff)
{
  char		msg[128];
  int		i;

  (void)buff;
  i = 0;
  while (s->team[i].name != NULL)
    {
      if (strcmp(user->team_name, s->team[i].name) == 0)
	{
	  sprintf(msg, "%d\n", s->team[i].nb);
	  safe_write(user->fd, strlen(msg), msg);
	  return (true);
	}
      ++i;
    }
  safe_write(user->fd, 2, "0\n");
  return (true);
}
