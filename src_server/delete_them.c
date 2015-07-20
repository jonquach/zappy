/*
** delete_them.c for qsd in /home/quach_a/backupzappy/Zappy/src_server
** 
** Made by Jonathan Quach
** Login  <jonathan.quach@epitech.eu>
** 
** Started on  Sun Jul  5 20:57:46 2015 Jonathan Quach
** Last update Sun Jul  5 20:57:46 2015 Jonathan Quach
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "server.h"

void		delete_them(t_server *s, t_user *user, int pos)
{
  t_user	*usr;

  usr = s->map[pos].user_list;
  while (usr != NULL)
    {
      if (usr->fd != user->fd)
	list_del_elem_at_position_no_close(&s->map[pos].user_list, usr->fd);
      usr = usr->next;
    }
}
