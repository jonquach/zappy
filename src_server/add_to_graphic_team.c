/*
** add_to_graphic_team.c for qsd in /home/quach_a/backupzappy/Zappy/src_server
** 
** Made by Jonathan Quach
** Login  <jonathan.quach@epitech.eu>
** 
** Started on  Sun Jul  5 20:58:07 2015 Jonathan Quach
** Last update Sun Jul  5 20:58:08 2015 Jonathan Quach
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "server.h"

t_bool		add_to_graphic_team(t_server *s, char *name, int fd)
{
  t_user	*new;

  if (strcmp(name, "GRAPHIC") != 0)
    return (false);
  if ((new = malloc(sizeof(*new))) == NULL)
    printstr(2, "Error: malloc\n");
  new->fd = fd;
  new->start = 1;
  new->direction = RIGHT;
  new->x = 0;
  new->y = 0;
  new->stone_list = NULL;
  new->next = s->gc_list;
  if ((new->team_name = strdup("GRAPHIC")) == NULL)
    return (false);
  s->gc_list = new;
  printf("**** Graphic interface connected\n");
  return (true);
}
