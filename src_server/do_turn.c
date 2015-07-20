/*
** do_turn.c for qsd in /home/quach_a/backupzappy/Zappy/src_server
** 
** Made by Jonathan Quach
** Login  <jonathan.quach@epitech.eu>
** 
** Started on  Sun Jul  5 20:58:30 2015 Jonathan Quach
** Last update Sun Jul  5 20:58:30 2015 Jonathan Quach
*/

#include <stdio.h>
#include "server.h"
#include "protocol.h"

void		turn_position_left(t_user **user)
{
  if ((*user)->direction == UP)
    (*user)->direction = LEFT;
  else if ((*user)->direction == RIGHT)
    (*user)->direction = UP;
  else if ((*user)->direction == DOWN)
    (*user)->direction = RIGHT;
  else if ((*user)->direction == LEFT)
    (*user)->direction = DOWN;
}

void		turn_position_right(t_user **user)
{
  if ((*user)->direction == UP)
    (*user)->direction = RIGHT;
  else if ((*user)->direction == RIGHT)
    (*user)->direction = DOWN;
  else if ((*user)->direction == DOWN)
    (*user)->direction = LEFT;
  else if ((*user)->direction == LEFT)
    (*user)->direction = UP;
}

t_bool		do_turn_left(t_server *s, t_user *user, char *buff)
{
  (void)buff;
  (void)s;
  turn_position_left(&user);
  send_ok(user->fd);
  update_player_pos(s->gc_list, user);
  return (true);
}

t_bool		do_turn_right(t_server *s, t_user *user, char *buff)
{
  (void)buff;
  (void)s;
  turn_position_right(&user);
  send_ok(user->fd);
  update_player_pos(s->gc_list, user);
  return (true);
}
