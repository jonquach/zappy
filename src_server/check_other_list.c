/*
** check_other_list.c for qsd in /home/quach_a/backupzappy/Zappy/src_server
** 
** Made by Jonathan Quach
** Login  <jonathan.quach@epitech.eu>
** 
** Started on  Sun Jul  5 20:57:52 2015 Jonathan Quach
** Last update Sun Jul  5 22:56:29 2015 jonathan kauch
*/

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "server.h"
#include "protocol.h"

t_bool			check_other_list(t_server *s, t_user *user)
{
  t_user		*tmp;

  tmp = s->other;
  if (tmp == NULL)
    return (false);
  while (tmp != NULL)
    {
      if (tmp->state == GHOST)
	{
	  tmp->fd = user->fd;
	  tmp->state = ACTIVE;
	  tmp->used = 1;
	  generate_food(s);
	  delete_user_of_map(s, user);
	  update_to_user_list(s, tmp);
	  printf("**** Ghost replaced by a new player at (%d, %d)\n",
		 tmp->x, tmp->y);
	  connect_player_to_egg(s->gc_list, user->fd);
	  connect_new_player(s->gc_list, user, -1);
	  delete_egg_of_map(s, tmp);
	  return (true);
	}
      tmp = tmp->next;
    }
  return (false);
}
