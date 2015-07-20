/*
** write_to_clients.c for  in /home/quach_a/backupzappy/Zappy/src_server
** 
** Made by Jonathan Quach
** Login  <jonathan.quach@epitech.eu>
** 
** Started on  Sun Jul  5 20:56:46 2015 Jonathan Quach
** Last update Sun Jul  5 20:56:47 2015 Jonathan Quach
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "server.h"
#include "toolbox.h"

void		write_to_clients(t_server *s, t_user *writer, char *buf)
{
  t_user	*users;
  char		msg[BUFFER_SIZE];

  memset(msg, 0, BUFFER_SIZE);
  strcat(msg, ":\t");
  strcat(msg, buf);
  strcat(msg, "\n");
  users = s->users;
  while (users != NULL)
    {
      if (users->fd != writer->fd)
	safe_write(users->fd, strlen(msg), msg);
      users = users->next;
    }
}

void		safe_write_to_clients(t_user *list, char *buffer)
{
  t_user	*tmp;

  tmp = list;
  while (tmp != NULL)
    {
      safe_write(tmp->fd, strlen(buffer), buffer);
      tmp = tmp->next;
    }
}
