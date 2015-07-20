/*
** print.c for  in /home/frayss_c/tmp_zappy/Zappy/toolbox
** 
** Made by Christophe Fraysse
** Login   <frayss_c@epitech.net>
** 
** Started on  Sun Jul  5 22:30:02 2015 Christophe Fraysse
** Last update Sun Jul  5 22:30:12 2015 Christophe Fraysse
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "server.h"
#include "toolbox.h"

extern t_server	g_s;

void		printstr(int fd, char const *str)
{
  if (write(fd, str, strlen(str)) == -1)
    {
      fprintf(stderr, "Error : write\n");
      perror("write");
      printf("tryyy tooooooo sennnndd -----> %s", str);
    }
  if (fd == 2)
    exit(EXIT_FAILURE);
}

void		disconnect_graphic(int fd)
{
  list_del_elem_at_position(&g_s.gc_list, fd);
}

void		safe_write(int cs2, int len, char const *buff)
{
  if (write(cs2, buff, len) == -1)
    {
      fprintf(stderr, "Error : write\n");
      perror("write");
      disconnect_graphic(cs2);
      printf("safe_write sennnndd -----> %s", buff);
    }
}

int		display_error(char const *str)
{
  if (write(2, str, strlen(str)) <= 0)
    fprintf(stderr, "Error : write\n");
  return (-1);
}
