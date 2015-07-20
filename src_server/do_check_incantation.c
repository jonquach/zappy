/*
** do_check_incantation.c for qsd in /home/quach_a/backupzappy/Zappy/src_server
** 
** Made by Jonathan Quach
** Login  <jonathan.quach@epitech.eu>
** 
** Started on  Sun Jul  5 20:57:42 2015 Jonathan Quach
** Last update Sun Jul  5 20:57:42 2015 Jonathan Quach
*/

#include <string.h>
#include <stdio.h>
#include "server.h"
#include "protocol.h"
#include "recipe.h"

void		add_incantation_to_input_list(t_server *s, t_input **input,
					      char *buff)
{
  t_input	*new;
  t_input	*tmp;

  tmp = *input;
  tmp->prev = tmp;
  while (tmp->next)
    {
      tmp->prev = tmp;
      tmp = tmp->next;
    }
  new = malloc_input_list();
  new->global_time = s->global_time + tmp->prev->cmd->delay;
  if ((new->buffer = strdup(buff)) == NULL)
    printstr(2, "Error: strdup\n");
  if ((new->cmd->name = strdup(INCANT)) == NULL)
    printstr(2, "Error: strdup\n");
  new->cmd->lenght = 11;
  new->cmd->delay = 1000000 * (300 / s->option->exec_time);
  new->cmd->func = &do_incantation;
  tmp->prev = tmp;
  tmp->next = new;
}

t_bool		do_check_incantation(t_server *s, t_user *u, char *buff)
{
  int		pos;

  pos = (u->y * s->option->width) + u->x;
  if (get_player_at_pos(&s->map[pos], u, g_recipe[u->level - 1].player_nb,
			true) == false)
    return (false);
  if (get_stone_combi_at_pos(&s->map[pos], g_recipe[u->level - 1].stone_combi,
			     true) == false)
    return (false);
  set_incantation_pos(s, u->x, u->y, u->level);
  safe_write(u->fd, 20, "elevation en cours\n");
  gc_do_incantation(s, u->x, u->y, u->level);
  add_incantation_to_input_list(s, &u->input, buff);
  return (true);
}
