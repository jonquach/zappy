/*
** check_isset_read.c for qsd in /home/quach_a/backupzappy/Zappy/src_server
** 
** Made by Jonathan Quach
** Login  <jonathan.quach@epitech.eu>
** 
** Started on  Sun Jul  5 20:58:11 2015 Jonathan Quach
** Last update Sun Jul  5 20:58:12 2015 Jonathan Quach
*/

#include <unistd.h>
#include <stdio.h>
#include "server.h"

void		check_isset_read(t_server *serv)
{
  t_user	*users;

  users = serv->users;
  if (FD_ISSET(serv->sock, &serv->readfds))
    {
      new_client(serv);
    }
  while (users != NULL)
    {
      if (FD_ISSET(users->fd, &serv->readfds))
	check_read(serv, users);
      users = users->next;
    }
}

