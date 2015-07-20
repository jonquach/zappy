/*
** check_cmd.c for qsd in /home/quach_a/backupzappy/Zappy/src_server
** 
** Made by Jonathan Quach
** Login  <jonathan.quach@epitech.eu>
** 
** Started on  Sun Jul  5 20:57:53 2015 Jonathan Quach
** Last update Sun Jul  5 20:57:54 2015 Jonathan Quach
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "server.h"
#include "cmd.h"
#include "protocol.h"

static t_bool	part_two(t_server *serv, t_user *user, char *tmp)
{
  if (add_to_graphic_team(serv, tmp, user->fd) == true)
    {
      delete_user_of_map(serv, user);
      list_del_elem_at_position_no_close(&serv->users, user->fd);
      gc_init(serv, serv->gc_list->fd);
      return (true);
    }
  if (add_team_name_to_user(serv, tmp, user->fd) == false)
    return (false);
  if (check_other_list(serv, user) ==  true)
    list_del_used_at_position_no_close(&serv->other, user->fd);
  else
    assigns_coord(serv, &user);
  if (send_information(serv, user->fd) == false)
    {
      list_del_elem_at_position(&serv->users, user->fd);
      return (false);
    }
  connect_new_player(serv->gc_list, user, -1);
  user->start = 0;
  return (true);

}

static t_bool	first_time(t_server *serv, t_user *user, char *buff)
{
  char		*tmp;

  if ((tmp = check_team_name(serv->option->team_name, buff)) == NULL)
    {
      list_del_elem_at_position(&serv->users, user->fd);
      return (false);
    }
  else
    {
      return (part_two(serv, user, tmp));
    }
  return (false);
}

static t_bool	check_if_cmd_need_param(t_server *serv, t_user *writer,
					char *buff, int i)
{
  if (i == 5 || i == 6 || i == 8)
    {
      if (strncmp(buff, g_cmd[i].name, g_cmd[i].lenght) == 0)
	{
	  if (strncmp(buff, g_cmd[i].name, g_cmd[i].lenght) == 0)
	    {
	      if ((is_input_list_empty(serv, writer, i, buff)) == true)
		return (true);
	      if (check_input_list_size(&writer->input) == true)
		push_back_input_list(serv, &writer->input, i, buff);
	      return (true);
	    }
	}
    }
  return (false);
}

static t_bool	check_cmd_tab(t_server *serv, t_user *writer,
			      char *buff)
{
  int		i;

  i = 0;
  while (i < 13)
    {
      if (check_if_cmd_need_param(serv, writer, buff, i) == false)
	{
	  if (strcmp(buff, g_cmd[i].name) == 0)
	    {
	      if ((is_input_list_empty(serv, writer, i, buff)) == true)
		return (true);
	      if (check_input_list_size(&writer->input) == true)
		push_back_input_list(serv, &writer->input, i, buff);
	      return (true);
	    }
	}
      else
	return (true);
      ++i;
    }
  return (false);
}

t_bool		check_cmd(t_server *serv, t_user *writer, char *buff)
{
  if (writer->start == 1)
    {
      if (first_time(serv, writer, buff) == false)
	return (false);
      return (true);
    }
  return (check_cmd_tab(serv, writer, buff));
}
