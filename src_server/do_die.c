/*
** do_die.c for qsd in /home/quach_a/backupzappy/Zappy/src_server
** 
** Made by Jonathan Quach
** Login  <jonathan.quach@epitech.eu>
** 
** Started on  Sun Jul  5 20:58:21 2015 Jonathan Quach
** Last update Sun Jul  5 20:58:22 2015 Jonathan Quach
*/

#include <stdio.h>
#include "server.h"
#include "protocol.h"
t_bool			do_die(t_server *s, t_user *user, char *buff)
{
  int			pos;

  (void)buff;
  safe_write(user->fd, 5, "mort\n");
  gc_do_die(s->gc_list, user);
  pos = user->y * s->option->width + user->x;
  list_del_elem_at_position_no_close(&s->map[pos].user_list, user->fd);
  list_del_elem_at_position(&s->users, user->fd);
  return (true);
}
