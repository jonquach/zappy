/*
** check_team.c for qsd in /home/quach_a/backupzappy/Zappy/src_server
** 
** Made by Jonathan Quach
** Login  <jonathan.quach@epitech.eu>
** 
** Started on  Sun Jul  5 20:57:50 2015 Jonathan Quach
** Last update Sun Jul  5 20:57:50 2015 Jonathan Quach
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "server.h"
#include "protocol.h"

t_bool		check_if_team_exist(char **list, char *str)
{
  int		i;

  i = 0;
  while (list[i] != NULL)
    {
      if (strcmp(list[i], str) == 0)
	return (true);
      if (strcmp(str, "GRAPHIC") == 0)
	return (true);
      ++i;
    }
  return (false);
}

char		*check_team_name(char **list, char *buf)
{
  int		j;
  int		i;
  char		*tmp;

  i = 0;
  j = 0;
  if ((tmp = malloc(sizeof(char) * strlen(buf) + 1)) == NULL)
    printstr(2, "Error : malloc\n");
  while (buf[i] && buf[i] != '\n')
    {
      tmp[j] = buf[i];
      ++i;
      j++;
    }
  tmp[j] = '\0';
  if (check_if_team_exist(list, tmp) == false)
    return (NULL);
  else
    return (tmp);
}

t_bool		decrement_nb_of_team(t_server *s, char *name)
{
  int		i;

  i = 0;
  while (s->team[i].name != NULL)
    {
      if (strcmp(s->team[i].name, name) == 0)
	{
	  if (s->team[i].nb >= 1)
	    {
	      s->team[i].nb--;
	      return (true);
	    }
	  else
	    return (false);
	}
      ++i;
    }
  return (false);
}

t_bool		add_team_name_to_user(t_server *s, char *name, int fd)
{
  t_user	*tmp;

  tmp = s->users;
  while (tmp != NULL)
    {
      if (tmp->fd == fd)
	{
	  tmp->team_name = name;
	  generate_food(s);
	  return (decrement_nb_of_team(s, name));
	}
      tmp = tmp->next;
    }
  return (false);
}
