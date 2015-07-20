/*
** assigns_coord.c for qsd in /home/quach_a/backupzappy/Zappy/src_server
** 
** Made by Jonathan Quach
** Login  <jonathan.quach@epitech.eu>
** 
** Started on  Sun Jul  5 20:57:55 2015 Jonathan Quach
** Last update Sun Jul  5 20:57:59 2015 Jonathan Quach
*/

#include <stdlib.h>
#include <stdio.h>
#include "server.h"

void		assigns_coord(t_server *s, t_user **user)
{
  int		pos;
  t_user	*new_elem_map;

  pos = rand() % (s->option->width * s->option->height);
  (*user)->x = s->map[pos].x;
  (*user)->y = s->map[pos].y;
  if ((new_elem_map = malloc(sizeof(*new_elem_map))) == NULL)
    printstr(2, "Error : malloc\n");
  new_elem_map->fd = (*user)->fd;
  new_elem_map->x = s->map[pos].x;
  new_elem_map->y = s->map[pos].y;
  new_elem_map->x_incantation = -1;
  new_elem_map->y_incantation = -1;
  new_elem_map->level = 1;
  new_elem_map->next = s->map[pos].user_list;
  s->map[pos].user_list = new_elem_map;
  printf("**** Added new player %d at (%d, %d)\n", s->nb, s->map[pos].x,
	 s->map[pos].y);
}
