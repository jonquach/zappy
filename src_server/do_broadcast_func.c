/*
** do_broadcast_func.c for  in /home/frayss_c/tmp_zappy/Zappy/src_server
** 
** Made by Christophe Fraysse
** Login   <frayss_c@epitech.net>
** 
** Started on  Sun Jul  5 21:46:04 2015 Christophe Fraysse
** Last update Sun Jul  5 22:25:08 2015 Christophe Fraysse
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "server.h"
#include "protocol.h"

int		calc_dir(t_user *tmp, e_msg_dir direction)
{
  int		msg_dir;
  int		dir;
  int		i;

  i = 0;
  if (tmp->direction == UP)
    msg_dir = MSG_UP;
  else if (tmp->direction == DOWN)
    msg_dir = MSG_DOWN;
  else if (tmp->direction == LEFT)
    msg_dir = MSG_LEFT;
  else if (tmp->direction == RIGHT)
    msg_dir = MSG_RIGHT;
  i = 0;
  while (msg_dir - i > 1)
    ++i;
  dir = direction - i;
  if (dir <= 0)
    dir = 8 + dir;
  return (dir);
}

char		*split_buffer(char *buff)
{
  int		i;
  char		**tab;
  char		*buffer;

  i = 1;
  if ((tab = str_to_wordtab(buff, " \n")) == NULL)
    return (NULL);
  if (tab[1] == NULL)
    return (NULL);
  if ((buffer = malloc(sizeof(char) * BUFFER_SIZE)) == NULL)
    printstr(2, "Error : malloc\n");
  memset(buffer, '\0', BUFFER_SIZE);
  while (tab[i] != NULL)
    {
      if (i != 1)
	strcat(buffer, " ");
      strcat(buffer, tab[i]);
      free(tab[i]);
      ++i;
    }
  return (buffer);
}
