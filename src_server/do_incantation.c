/*
** do_incantation.c for qsd in /home/quach_a/backupzappy/Zappy/src_server
** 
** Made by Jonathan Quach
** Login  <jonathan.quach@epitech.eu>
** 
** Started on  Sun Jul  5 20:57:35 2015 Jonathan Quach
** Last update Sun Jul  5 20:57:36 2015 Jonathan Quach
*/

#include <string.h>
#include <stdio.h>
#include "server.h"
#include "protocol.h"
#include "recipe.h"

void		level_up_player_at_pos(t_server *s, int x, int y,
				       int old_level)
{
  t_user	*tmp;
  char		buffer[20];

  tmp = s->map[y * s->option->width + x].user_list;
  while (tmp != NULL)
    {
      if (tmp->level == old_level && tmp->x_incantation == x &&
	  tmp->y_incantation == y)
	{
	  ++tmp->level;
	  memset(buffer, '\0', 20);
	  sprintf(buffer, "niveau actuel : %d\n", tmp->level);
	  safe_write(tmp->fd, 19, buffer);
	  update_to_user_list(s, tmp);
	}
      tmp = tmp->next;
    }
}

t_bool		remove_stone_combi_at_pos(t_server *s, t_map *map,
					  char *stone_combi)
{
  int		i;

  i = 0;
  while (i < 7)
    {
      map->stone_list[i].nb -= (stone_combi[i] - '0');
      ++i;
    }
  update_box_content(s, -1, map->y * s->option->width + map->x);
  return (true);
}

void		set_incantation_pos(t_server *s, int x, int y, int level)
{
  t_user	*tmp;

  tmp = s->map[y * s->option->width + x].user_list;
  while (tmp != NULL)
    {
      if (tmp->level == level && tmp->x == x && tmp->y == y)
	{
	  tmp->x_incantation = x;
	  tmp->y_incantation = y;
	  update_to_user_list(s, tmp);
	}
      tmp = tmp->next;
    }
}

t_bool		do_incantation_ko(t_server *s, t_user *u, char *buff)
{
  (void)s;
  (void)u;
  (void)buff;
  return (false);
}

t_bool		do_incantation(t_server *s, t_user *u, char *buff)
{
  int		pos;

  (void)buff;
  pos = (u->y * s->option->width) + u->x;
  if (u->x_incantation != u->x || u->y_incantation != u->y ||
      get_player_at_pos(&s->map[pos], u, g_recipe[u->level - 1].player_nb,
  		        false) == false ||
      get_stone_combi_at_pos(&s->map[pos], g_recipe[u->level - 1].stone_combi,
  			     false) == false)
    {
      gc_end_incantation(s->gc_list, u->x, u->y, "ko");
      return (false);
    }
  remove_stone_combi_at_pos(s, &s->map[pos],
			    g_recipe[u->level - 1].stone_combi);
  level_up_player_at_pos(s, u->x, u->y, u->level);
  gc_end_incantation(s->gc_list, u->x, u->y, "ok");
  update_player_level(s, u->x, u->y, u->level);
  set_incantation_pos(s, u->x, u->y, u->level + 1);
  return (true);
}
