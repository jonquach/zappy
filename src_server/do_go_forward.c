/*
** do_go_forward.c for qsd in /home/quach_a/backupzappy/Zappy/src_server
** 
** Made by Jonathan Quach
** Login  <jonathan.quach@epitech.eu>
** 
** Started on  Sun Jul  5 20:58:23 2015 Jonathan Quach
** Last update Sun Jul  5 20:58:24 2015 Jonathan Quach
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "server.h"
#include "protocol.h"

static t_bool		up_right(t_server *s, t_user *user)
{
  if (user->direction == UP)
    {
      delete_user_of_map(s, user);
      --user->x;
      if (user->x == -1)
	user->x += s->option->width;
      add_user_in_the_map(s, user);
    }
  else if (user->direction == RIGHT)
    {
      delete_user_of_map(s, user);
      --user->y;
      if (user->y == -1)
	user->y += s->option->height;
      add_user_in_the_map(s, user);
    }
  else
    return (false);
  return (true);
}

static t_bool		down_left(t_server *s, t_user *user)
{
  if (user->direction == DOWN)
    {
      delete_user_of_map(s, user);
      ++user->x;
      if (user->x == s->option->width)
	user->x = 0;
      add_user_in_the_map(s, user);
    }
  else if (user->direction == LEFT)
    {
      delete_user_of_map(s, user);
      ++user->y;
      if (user->y == s->option->height)
	user->y = 0;
      add_user_in_the_map(s, user);
    }
  else
    return (false);
  return (true);
}

t_bool			do_go_forward(t_server *s, t_user *user, char *buff)
{
  (void)buff;
  if (up_right(s, user) == false)
    if (down_left(s, user) == false)
      return (false);
  send_ok(user->fd);
  update_player_pos(s->gc_list, user);
  return (true);
}
