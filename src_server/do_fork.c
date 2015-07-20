/*
** do_fork.c for qsd in /home/quach_a/backupzappy/Zappy/src_server
** 
** Made by Jonathan Quach
** Login  <jonathan.quach@epitech.eu>
** 
** Started on  Sun Jul  5 20:57:38 2015 Jonathan Quach
** Last update Sun Jul  5 20:57:38 2015 Jonathan Quach
*/

#include <stdio.h>
#include "server.h"
#include "protocol.h"

t_bool			do_fork(t_server *s, t_user *user, char *buff)
{
  (void)buff;
  if (add_egg_in_the_map(s, user) == false)
    return (false);
  add_egg_in_list(s, user->team_name, user->x, user->y);
  send_ok(user->fd);
  gc_do_fork(s->gc_list, user, s->other->fd);
  return (true);
}
