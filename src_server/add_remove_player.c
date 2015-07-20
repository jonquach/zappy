/*
** add_remove_player.c for qsd in /home/quach_a/backupzappy/Zappy/src_server
** 
** Made by Jonathan Quach
** Login  <jonathan.quach@epitech.eu>
** 
** Started on  Sun Jul  5 20:58:00 2015 Jonathan Quach
** Last update Sun Jul  5 20:58:00 2015 Jonathan Quach
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "server.h"
#include "protocol.h"

t_bool		delete_user_of_map(t_server *s, t_user *user)
{
  int		i;

  i = user->y * s->option->width + user->x;
  if (i < s->option->width * s->option->height)
    list_del_elem_at_position_no_close(&s->map[i].user_list, user->fd);
  return (false);
}

t_bool		delete_egg_of_map(t_server *s, t_user *user)
{
  int		i;

  i = user->y * s->option->width + user->x;
  if (i < s->option->width * s->option->height)
    list_del_egg_at_position_no_close(&s->map[i].user_list, user->fd);
  return (false);
}

t_bool		update_to_user_list(t_server *s, t_user *user)
{
  t_user	*tmp;

  tmp = s->users;
  while (tmp != NULL)
    {
      if (tmp->fd == user->fd)
	{
	  tmp->x = user->x;
	  tmp->y = user->y;
	  tmp->x_incantation = user->x_incantation;
	  tmp->y_incantation = user->y_incantation;
	  tmp->direction = user->direction;
	  tmp->level = user->level;
	  tmp->state = user->state;
	  return (true);
	}
      tmp = tmp->next;
    }
  return (false);
}

t_bool		add_user_in_the_map(t_server *s, t_user *user)
{
  int		i;
  t_user	*tmp;

  i = user->y * s->option->width + user->x;
  if (i < s->option->width * s->option->height)
    {
      if ((tmp = malloc(sizeof(*tmp))) == NULL)
	return (false);
      tmp->fd = user->fd;
      tmp->direction = user->direction;
      tmp->x = user->x;
      tmp->y = user->y;
      tmp->x_incantation = user->x_incantation;
      tmp->y_incantation = user->y_incantation;
      tmp->level = user->level;
      tmp->state = user->state;
      update_to_user_list(s, user);
      tmp->next = s->map[i].user_list;
      s->map[i].user_list = tmp;
      update_player_pos(s->gc_list, user);
      return (true);
    }
  return (false);
}

t_bool		add_egg_in_the_map(t_server *s, t_user *user)
{
  int		i;
  t_user	*tmp;

  i = user->y * s->option->width + user->x;
  if (i < s->option->width * s->option->height)
    {
      if ((tmp = malloc(sizeof(*tmp))) == NULL)
        return (false);
      tmp->fd = user->fd;
      tmp->direction = user->direction;
      tmp->x = user->x;
      tmp->y = user->y;
      tmp->x_incantation = user->x_incantation;
      tmp->y_incantation = user->y_incantation;
      tmp->state = EGG;
      update_to_user_list(s, user);
      tmp->next = s->map[i].user_list;
      s->map[i].user_list = tmp;
      return (true);
    }
  return (false);
}
