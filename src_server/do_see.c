/*
** do_see.c for qsd in /home/quach_a/backupzappy/Zappy/src_server
** 
** Made by Jonathan Quach
** Login  <jonathan.quach@epitech.eu>
** 
** Started on  Sun Jul  5 20:58:27 2015 Jonathan Quach
** Last update Sun Jul  5 21:36:57 2015 Christophe Fraysse
*/

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "server.h"

void	do_see_up(t_server *s, t_user *user, char *buffer)
{
  int	vision;
  int	x;
  int	y;
  int	pos;
  int	y_tmp;

  vision = 0;
  while (vision < user->level + 1)
    {
      if ((x = user->x - vision) < 0)
	while ((x += s->option->width) < 0);
      y = user->y + vision;
      while (y >= user->y - vision)
	{
	  y_tmp = set_tmp_coord(y, s->option->height);
	  pos = y_tmp * s->option->width + x;
	  get_map_at_pos(&s->map[pos], buffer);
	  --y;
	  if (y != user->y - vision - 1 || vision != user->level)
	    strcat(buffer, ",");
	}
      ++vision;
    }
}

void	do_see_down(t_server *s, t_user *user, char *buffer)
{
  int	vision;
  int	x;
  int	y;
  int	pos;
  int	y_tmp;

  vision = 0;
  while (vision < user->level + 1)
    {
      x = (user->x + vision) % s->option->width;
      y = user->y - vision;
      while (y <= user->y + vision)
	{
	  y_tmp = set_tmp_coord(y, s->option->height);
	  pos = y_tmp * s->option->width + x;
	  get_map_at_pos(&s->map[pos], buffer);
	  ++y;
	  if (y != user->y + vision + 1 || vision != user->level)
	    strcat(buffer, ",");
	}
      ++vision;
    }
}

void	do_see_right(t_server *s, t_user *user, char *buffer)
{
  int	vision;
  int	x;
  int	y;
  int	pos;
  int	x_tmp;

  vision = 0;
  while (vision < user->level + 1)
    {
      if ((y = user->y - vision) < 0)
	while ((y += s->option->height) < 0);
      x = user->x - vision;
      while (x <= user->x + vision)
	{
	  x_tmp = set_tmp_coord(x, s->option->width);
	  pos = y * s->option->width + x_tmp;
	  get_map_at_pos(&s->map[pos], buffer);
	  ++x;
	  if (x != user->x + vision + 1 || vision != user->level)
	    strcat(buffer, ",");
	}
      ++vision;
    }
}

void	do_see_left(t_server *s, t_user *user, char *buffer)
{
  int	vision;
  int	x;
  int	y;
  int	pos;
  int	x_tmp;

  vision = 0;
  while (vision < user->level + 1)
    {
      y = (user->y + vision) % s->option->height;
      x = user->x + vision;
      while (x >= user->x - vision)
	{
	  x_tmp = set_tmp_coord(x, s->option->width);
	  pos = y * s->option->width + x_tmp;
	  get_map_at_pos(&s->map[pos], buffer);
	  --x;
	  if (x != user->x - vision - 1 || vision != user->level)
	    strcat(buffer, ",");
	}
      ++vision;
    }
}

t_bool	do_see(t_server *s, t_user *user, char *buff)
{
  static char	buffer[65536];

  memset(buffer, '\0', 65536);
  strcat(buffer, "{");
  if (user->direction == UP)
    do_see_up(s, user, buffer);
  else if (user->direction == DOWN)
    do_see_down(s, user, buffer);
  else if (user->direction == RIGHT)
    do_see_right(s, user, buffer);
  else if (user->direction == LEFT)
    do_see_left(s, user, buffer);
  strcat(buffer, "}\n");
  safe_write(user->fd, strlen(buffer), buffer);
  (void)buff;
  return (true);
}
