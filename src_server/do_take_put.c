/*
** do_take_put.c for qsd in /home/quach_a/backupzappy/Zappy/src_server
** 
** Made by Jonathan Quach
** Login  <jonathan.quach@epitech.eu>
** 
** Started on  Sun Jul  5 20:57:31 2015 Jonathan Quach
** Last update Sun Jul  5 20:57:31 2015 Jonathan Quach
*/

#include <string.h>
#include <stdio.h>
#include "server.h"
#include "protocol.h"

static t_bool		add_stone_to_user(t_server *s, t_user *user,
					  char *stone)
{
  int			i;

  i = 0;
  while (i < 7)
    {
      if (strcmp(user->stone_list[i].name, stone) == 0)
	{
	  if (i == 0)
	    user->food += 1000000 * (126 / s->option->exec_time);
	  user->stone_list[i].nb++;
	  return (false);
	}
      ++i;
    }
  return (false);
}

t_bool			do_take(t_server *s, t_user *user, char *buff)
{
  int			pos;
  int			i;
  char			**tab;

  if ((tab = str_to_wordtab(buff, " \n")) == NULL)
    return (false);
  i = 0;
  pos = user->y * s->option->width + user->x;
  while (i < 7)
    {
      if (tab[1] && strcmp(s->map[pos].stone_list[i].name, tab[1]) == 0
	  && s->map[pos].stone_list[i].nb > 0)
	{
	  update_box_content(s, -1, pos);
	  s->map[pos].stone_list[i].nb--;
	  add_stone_to_user(s, user, tab[1]);
	  send_ok(user->fd);
	  gc_do_take(s, user, i);
	  free_wordtab(tab);
	  return (true);
	}
      ++i;
    }
  free_wordtab(tab);
  return (false);
}

static t_bool		remove_stone_to_user(t_server *s, t_user *user,
					     char *stone)
{
  int			i;

  i = 0;
  while (i < 7)
    {
      if (strcmp(user->stone_list[i].name, stone) == 0)
	{
	  if (i == 0)
	    user->food -= 1000000 * (126 / s->option->exec_time);
	  if (user->stone_list[i].nb > 0)
	    {
	      user->stone_list[i].nb--;
	      return (true);
	    }
	  else
	    return (false);
	}
      ++i;
    }
  return (false);
}

t_bool			do_put(t_server *s, t_user *user, char *buff)
{
  int			pos;
  int			i;
  char			**tab;

  if ((tab = str_to_wordtab(buff, " \n")) == NULL)
    return (false);
  i = 0;
  pos = user->y * s->option->width + user->x;
  while (i < 7)
    {
      if (tab[1] && strcmp(s->map[pos].stone_list[i].name, tab[1]) == 0)
	{
	  update_box_content(s, -1, pos);
	  s->map[pos].stone_list[i].nb++;
	  if (remove_stone_to_user(s, user, tab[1]) == false)
	    return (false);
	  send_ok(user->fd);
	  gc_do_put(s, user, i);
	  free_wordtab(tab);
	  return (true);
	}
      ++i;
    }
  free_wordtab(tab);
  return (false);
}
