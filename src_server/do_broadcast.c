/*
** do_broadcast.c for qsd in /home/quach_a/backupzappy/Zappy/src_server
** 
** Made by Jonathan Quach
** Login  <jonathan.quach@epitech.eu>
** 
** Started on  Sun Jul  5 20:58:19 2015 Jonathan Quach
** Last update Sun Jul  5 22:24:47 2015 Christophe Fraysse
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "server.h"
#include "protocol.h"

e_msg_dir		get_dir_x(t_server *s, t_user *user, t_user *tmp)
{
  int			diff_x;

  diff_x = 0;
  if (user->x == tmp->x)
    return (NONE);
  if (user->x > tmp->x)
    diff_x = user->x - tmp->x;
  else
    diff_x = tmp->x - user->x;
  if (diff_x <= (s->option->width / 2))
    {
      if (user->x > tmp->x)
	return (MSG_DOWN);
      return (MSG_UP);
    }
  else
    {
      if (user->x > tmp->x)
	return (MSG_UP);
      return (MSG_DOWN);
    }
}

e_msg_dir		get_dir_y(t_server *s, t_user *user, t_user *tmp)
{
  int			diff_y;

  diff_y = 0;
  if (user->y == tmp->y)
    return (NONE);
  if (user->y > tmp->y)
    diff_y = user->y - tmp->y;
  else
    diff_y = tmp->y - user->y;
  if (diff_y <= (s->option->height / 2))
    {
      if (user->y > tmp->y)
	return (MSG_LEFT);
      return (MSG_RIGHT);
    }
  else
    {
      if (user->y > tmp->y)
	return (MSG_RIGHT);
      return (MSG_LEFT);
    }
}

e_msg_dir		get_dir(t_server *s, t_user *user, t_user *tmp)
{
  e_msg_dir		direction_x;
  e_msg_dir		direction_y;

  direction_y = get_dir_y(s, user, tmp);
  direction_x = get_dir_x(s, user, tmp);
  if (direction_x == NONE && direction_y == NONE)
    return (NONE);
  else if (direction_x == NONE && direction_y == MSG_RIGHT)
    return (MSG_RIGHT);
  else if (direction_x == NONE && direction_y == MSG_LEFT)
    return (MSG_LEFT);
  else if (direction_x == MSG_UP && direction_y == NONE)
    return (MSG_UP);
  else if (direction_x == MSG_DOWN && direction_y == NONE)
    return (MSG_DOWN);
  else if (direction_x == MSG_UP && direction_y == MSG_LEFT)
    return (MSG_UP_LEFT);
  else if (direction_x == MSG_DOWN && direction_y == MSG_LEFT)
    return (MSG_DOWN_LEFT);
  else if (direction_x == MSG_DOWN && direction_y == MSG_RIGHT)
    return (MSG_DOWN_RIGHT);
  else if (direction_x == MSG_UP && direction_y == MSG_RIGHT)
    return (MSG_UP_RIGHT);
  return (NONE);
}

t_bool			broadcast_text(t_server *s, t_user *user,
				       t_user *tmp, char *buffer)
{
  e_msg_dir		direction;
  int			dir;
  char			msg[1024];

  direction = get_dir(s, user, tmp);
  if (direction == NONE)
    dir = 0;
  else
    dir = calc_dir(tmp, direction);
  memset(msg, '\0', 1024);
  sprintf(msg, "message %d,%s\n", dir, buffer);
  safe_write(tmp->fd, strlen(msg), msg);
  return (true);
}

t_bool			do_broadcast(t_server *s, t_user *user, char *buff)
{
  t_user		*tmp;
  char			*buffer;

  tmp = s->users;
  if ((buffer = split_buffer(buff)) == NULL)
    return (false);
  while (tmp != NULL)
    {
      if (tmp->fd != user->fd)
	if (broadcast_text(s, user, tmp, buffer) == false)
	  return (false);
      tmp = tmp->next;
    }
  send_ok(user->fd);
  gc_do_broadcast(s->gc_list, user, buff);
  return (true);
}
