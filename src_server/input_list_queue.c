/*
** input_list_queue.c for qsd in /home/quach_a/backupzappy/Zappy/src_server
** 
** Made by Jonathan Quach
** Login  <jonathan.quach@epitech.eu>
** 
** Started on  Sun Jul  5 20:58:40 2015 Jonathan Quach
** Last update Sun Jul  5 20:58:40 2015 Jonathan Quach
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "server.h"
#include "cmd.h"

void		check_input_list(t_server *server, t_user *user)
{
  t_user	*tmp;

  tmp = user;
  while (tmp != NULL)
    {
      if (tmp->input != NULL && tmp->input->cmd != NULL &&
      	  tmp->input->cmd->name != NULL)
	{
	  if (server->global_time >= tmp->input->global_time
	      + tmp->input->cmd->delay)
	    {
	      puts(tmp->input->cmd->name);
	      if (tmp->input->cmd->func(server, tmp,
					tmp->input->buffer) == false)
		safe_write(tmp->fd, 3, "ko\n");
	      pop_front_input_list(&tmp->input);
	    }
	}
      tmp = tmp->next;
    }
}

static void	add_cmd_to_input_list(t_server *server, t_cmd *cmd, int i)
{
  t_cmd		*new;
  t_cmd		*tmp;

  tmp = cmd;
  if ((new = malloc(sizeof(t_cmd))) == NULL)
    printstr(2, "Error: malloc\n");
  if ((tmp->name = strdup(g_cmd[i].name)) == NULL)
    printstr(2, "Error: strdup\n");
  tmp->lenght = g_cmd[i].lenght;
  tmp->delay = 1000000 * (g_cmd[i].delay / server->option->exec_time);
  tmp->func = g_cmd[i].func;
  tmp = new;
}

static t_bool	create_input_list(t_server *server, t_user *user, int i,
				  char *buffer)
{
  t_input	*tmp;

  tmp = user->input;
  tmp->global_time = server->global_time;
  if ((tmp->buffer = strdup(buffer)) == NULL)
    printstr(2, "Error: strdup\n");
  add_cmd_to_input_list(server, user->input->cmd, i);
  return (true);
}

t_bool		is_input_list_empty(t_server *server, t_user *user, int i,
				    char *buffer)
{
  if (user->input == NULL || user->input->global_time == 0)
    {
      user->input = malloc_input_list();
      return (create_input_list(server, user, i, buffer));
    }
  return (false);
}
