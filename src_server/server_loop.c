/*
** server_loop.c for qsd in /home/quach_a/backupzappy/Zappy/src_server
** 
** Made by Jonathan Quach
** Login  <jonathan.quach@epitech.eu>
** 
** Started on  Sun Jul  5 20:56:51 2015 Jonathan Quach
** Last update Sun Jul  5 21:31:15 2015 Christophe Fraysse
*/

#include <time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "server.h"
#include "protocol.h"

static void		check_egg(t_server *serv)
{
  t_user		*tmp;
  float			time;

  tmp = serv->other;
  serv->other_size = 0;
  while (tmp != NULL)
    {
      time = (tmp->global_time + (1000000 * (600 / serv->option->exec_time)));
      if (serv->global_time >= time)
	{
	  if (tmp->state == EGG)
	    {
	      tmp->state = GHOST;
	      gc_egg_hatch(serv->gc_list, tmp->fd);
	      generate_food(serv);
	      tmp->food = 1000000 * (126 * 10 / serv->option->exec_time);
	      tmp->food_time = serv->global_time;
	    }
	}
      ++serv->other_size;
      tmp = tmp->next;
    }
}

void			check_users_food(t_server *s, t_user *u)
{
  t_user		*tmp;
  double		diff;

  tmp = u;
  if (tmp == NULL)
    return;
  while (tmp != NULL)
    {
      diff = s->global_time - tmp->food_time;
      tmp->food -= diff;
      tmp->stone_list[0].nb = tmp->food * s->option->exec_time / 1000000 / 126;
      tmp->food_time = s->global_time;
      if (tmp->food <= 0)
	{
	  if (u->team_name && strcmp(u->team_name,
				     "GRAPHIC") != 0)
	    do_die(s, tmp, NULL);
	}
      tmp = tmp->next;
    }
}

void			check_others_food(t_server *s, t_user *tmp)
{
  t_user		*tmp_prev;
  double		diff;

  tmp_prev = NULL;
  while (tmp != NULL)
    {
      if (tmp->state == GHOST)
	{
	  diff = s->global_time - tmp->food_time;
	  tmp->food -= diff;
	  tmp->stone_list[0].nb = tmp->food * s->option->exec_time
	    / 1000000 / 126;
	  tmp->food_time = s->global_time;
	  if (tmp->food <= 0)
	    {
	      if (tmp_prev != NULL)
	  	tmp_prev->next = tmp->next;
	      else
	  	s->other = tmp->next;
	    }
	}
      tmp_prev = tmp;
      tmp = tmp->next;
    }
}

t_bool			into_loop(t_server *serv)
{
  struct timeval	timeout;
  int			ret;
  double		usec;

  usec = 1000000 / serv->option->exec_time;
  timeout.tv_sec = 0;
  timeout.tv_usec = usec;
  ret = select(serv->max_fd + 1, &serv->readfds, NULL, NULL, &timeout);
  if (timeout.tv_usec == 0)
    serv->global_time += usec;
  else
    serv->global_time += timeout.tv_usec;
  if (serv->users != NULL)
    check_input_list(serv, serv->users);
  check_egg(serv);
  if (ret == -1)
    return (false);
  else if (ret)
    check_isset_read(serv);
  check_users_food(serv, serv->users);
  check_others_food(serv, serv->other);
  return (true);
}

t_bool			server_loop(t_server *serv)
{
  serv->err = true;
  while (serv->err)
    {
      if (check_winner(serv) == true)
        {
          remove_all(serv);
	  return (true);
        }
      reset_fds(serv);
      set_all_fds(serv);
      serv->err = into_loop(serv);
    }
  return (false);
}
