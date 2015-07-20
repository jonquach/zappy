/*
** check_winner.c for qsd in /home/quach_a/backupzappy/Zappy/src_server
** 
** Made by Jonathan Quach
** Login  <jonathan.quach@epitech.eu>
** 
** Started on  Sun Jul  5 20:57:48 2015 Jonathan Quach
** Last update Sun Jul  5 20:57:48 2015 Jonathan Quach
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "server.h"
#include "protocol.h"

t_bool		check_winner_team(t_server *s, int *team_count, int i)
{
  t_user	*tmp;
  int		j;

  tmp = s->users;
  while (tmp != NULL)
    {
      j = 0;
      if (tmp->level == 8)
	{
	  while (j < i)
	    {
	      if (strcmp(tmp->team_name, s->team[j].name) == 0)
		++team_count[j];
	      if (team_count[j] >= 6)
		{
		  gc_end_game(s->gc_list, tmp->team_name);
		  return (true);
		}
	      ++j;
	    }
	}
      tmp = tmp->next;
    }
  return (false);
}

t_bool		check_winner(t_server *s)
{
  int		*team_count;
  int		i;
  int		j;

  i = 0;
  while (s->team[i].name != NULL)
    ++i;
  if ((team_count = malloc(sizeof(int) * i)) == NULL)
    printstr(2, "Error : malloc\n");
  j = 0;
  while (j < i)
    {
      team_count[j] = 0;
      ++j;
    }
  return (check_winner_team(s, team_count, i));
}
