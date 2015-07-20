/*
** get_map_at_pos.c for qsd in /home/quach_a/backupzappy/Zappy/src_server
** 
** Made by Jonathan Quach
** Login  <jonathan.quach@epitech.eu>
** 
** Started on  Sun Jul  5 20:58:33 2015 Jonathan Quach
** Last update Sun Jul  5 21:24:37 2015 Christophe Fraysse
*/

#include <stdio.h>
#include <string.h>
#include "server.h"

t_bool		get_player_at_pos(t_map *map, t_user *u, int expected_nb,
				  t_bool exact)
{
  t_user	*tmp;
  int		nb_total;
  int		nb_at_lvl;

  tmp = map->user_list;
  nb_total = 0;
  nb_at_lvl = 0;
  while (tmp != NULL)
    {
      if (tmp->level == u->level && tmp->x == u->x &&
	  tmp->y == u->y)
	++nb_at_lvl;
      ++nb_total;
      tmp = tmp->next;
    }
  if (exact == true && nb_at_lvl == expected_nb
      && nb_total == expected_nb)
    return (true);
  else if (exact == false && nb_at_lvl == expected_nb)
    return (true);
  return (false);
}

t_bool		get_stone_combi_at_pos(t_map *map, char *stone_combi,
				       t_bool exact)
{
  int		i;

  i = 1;
  if (exact == true)
    {
      while (i < 7)
	{
	  if (map->stone_list[i].nb != stone_combi[i] - '0')
	    return (false);
	  ++i;
	}
    }
  else
    {
      while (i < 7)
	{
	  if (map->stone_list[i].nb < stone_combi[i] - '0')
	    return (false);
	  ++i;
	}
    }
  return (true);
}

void		get_map_at_pos(t_map *map, char *buffer)
{
  int		i;
  int		j;
  t_user	*tmp;

  tmp = map->user_list;
  while (tmp != NULL)
    {
      if (tmp->state != EGG && tmp->state != GHOST)
	strcat(buffer, " joueur");
      tmp = tmp->next;
    }
  i = 0;
  j = 0;
  while (i < 7)
    {
      j = map->stone_list[i].nb;
      while (j > 0)
	{
	  strcat(buffer, " ");
	  strcat(buffer, map->stone_list[i].name);
	  --j;
	}
      ++i;
    }
}
