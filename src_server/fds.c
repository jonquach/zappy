/*
** fds.c for qsd in /home/quach_a/backupzappy/Zappy/src_server
** 
** Made by Jonathan Quach
** Login  <jonathan.quach@epitech.eu>
** 
** Started on  Sun Jul  5 20:57:28 2015 Jonathan Quach
** Last update Sun Jul  5 20:57:29 2015 Jonathan Quach
*/

#include <string.h>
#include <stdlib.h>
#include "server.h"

void		set_fd(int fd, t_server *s)
{
  FD_SET(fd, &s->readfds);
  if (s->max_fd < fd)
    s->max_fd = fd;
}

void		set_all_fds(t_server *s)
{
  t_user	*users;

  set_fd(s->sock, s);
  users = s->users;
  while (users != NULL)
    {
      set_fd(users->fd, s);
      users = users->next;
    }
}

void		reset_fds(t_server *s)
{
  FD_ZERO(&s->readfds);
  s->max_fd = 0;
}
