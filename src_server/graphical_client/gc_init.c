/*
** gc_init.c for qsd in /home/quach_a/backupzappy/Zappy/src_server/graphical_client
** 
** Made by Jonathan Quach
** Login  <jonathan.quach@epitech.eu>
** 
** Started on  Sun Jul  5 20:59:15 2015 Jonathan Quach
** Last update Sun Jul  5 22:06:51 2015 Christophe Fraysse
*/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "server.h"
#include "protocol.h"
#include "toolbox.h"

static void	send_team_name(t_server *s, int fd)
{
  char		buffer[4096];
  int		i;

  i = 0;
  while (s->team[i].name != NULL)
    {
      memset(buffer, '\0', 4096);
      sprintf(buffer, TEAM_NAME, s->team[i].name);
      safe_write(fd, strlen(buffer), buffer);
      ++i;
    }
}

static void	send_map_content(t_server *s, int fd, int map_size)
{
  int		i;

  i = 0;
  while (i < map_size)
    {
      update_box_content(s, fd, i);
      ++i;
    }
}

static void	send_map_size(t_server *s, int fd)
{
  char		buffer[4096];

  memset(buffer, '\0', 4096);
  sprintf(buffer, MAP_SIZE, s->option->width, s->option->height);
  strcat(buffer, "\n");
  safe_write(fd, strlen(buffer), buffer);
}

static void	send_all_users(t_server *s, int fd)
{
  t_user	*tmp;

  tmp = s->users;
  while (tmp != NULL)
    {
      connect_new_player(s->gc_list, tmp, fd);
      tmp = tmp->next;
    }
}

void		gc_init(t_server *s, int fd)
{
  send_map_size(s, fd);
  update_game_time(s, fd);
  send_map_content(s, fd, s->option->width * s->option->height);
  send_team_name(s, fd);
  send_all_users(s, fd);
}
