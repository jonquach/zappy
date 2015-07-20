/*
** input_list_func.c for qsd in /home/quach_a/backupzappy/Zappy/src_server
** 
** Made by Jonathan Quach
** Login  <jonathan.quach@epitech.eu>
** 
** Started on  Sun Jul  5 20:57:17 2015 Jonathan Quach
** Last update Sun Jul  5 20:57:20 2015 Jonathan Quach
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "server.h"
#include "cmd.h"

t_input		*malloc_input_list()
{
  t_input	*input_list;

  if ((input_list = malloc(sizeof(t_input))) == NULL)
    printstr(2, "Error : malloc\n");
  if ((input_list->cmd = malloc(sizeof(t_cmd))) == NULL)
    printstr(2, "Error : malloc\n");
  input_list->global_time = 0;
  input_list->cmd->name = NULL;
  input_list->buffer = "\0";
  input_list->prev = NULL;
  input_list->next = NULL;
  input_list->cmd->name = NULL;
  return (input_list);
}

t_bool		check_input_list_size(t_input **input)
{
  int		i;
  t_input	*tmp;

  i = 0;
  tmp = *input;
  if (tmp != NULL)
    {
      while (tmp->next != NULL)
	{
	  tmp = tmp->next;
	  ++i;
	}
    }
  if (i >= 10)
    return (false);
  return (true);
}

void		push_back_input_list(t_server *server, t_input **input,
				     int i, char *buffer)
{
  t_input	*tmp;
  t_input	*tmp_prev;
  t_input	*new;

  tmp = *input;
  tmp_prev = NULL;
  tmp->prev = tmp;
  while (tmp->next != NULL)
    {
      tmp_prev = tmp;
      tmp = tmp->next;
      tmp->prev = tmp_prev;
    }
  new = malloc_input_list();
  new->global_time = tmp->prev->global_time + tmp->prev->cmd->delay;
  if ((new->buffer = strdup(buffer)) == NULL)
    printstr(2, "Error: strdup\n");
  if ((new->cmd->name = strdup(g_cmd[i].name)) == NULL)
    printstr(2, "Error: strdup\n");
  new->cmd->lenght = g_cmd[i].lenght;
  new->cmd->delay = 1000000 * (g_cmd[i].delay / server->option->exec_time);
  new->cmd->func = g_cmd[i].func;
  tmp->next = new;
}

t_bool		pop_front_input_list(t_input **input)
{
  t_input	*tmp;

  tmp = *input;

  if (tmp != NULL)
    {
      *input = tmp->next;
      if (tmp->next == NULL)
	return (false);
    }
  return (true);
}
