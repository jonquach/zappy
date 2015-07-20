/*
** gc_cmd2.c for qsd in /home/quach_a/backupzappy/Zappy/src_server/graphical_client
** 
** Made by Jonathan Quach
** Login  <jonathan.quach@epitech.eu>
** 
** Started on  Sun Jul  5 20:59:16 2015 Jonathan Quach
** Last update Sun Jul  5 20:59:17 2015 Jonathan Quach
*/

#include <string.h>
#include <stdio.h>
#include "server.h"
#include "protocol.h"

void	gc_do_take(t_server *s, t_user *u, int stone)
{
  char	buffer[512];

  memset(buffer, '\0', 512);
  sprintf(buffer, DO_TAKE, u->fd, stone);
  safe_write_to_clients(s->gc_list, buffer);
  gc_do_inventory(s->gc_list, u);
  update_box_content(s, -1, u->y * s->option->width + u->x);
}

void	gc_do_put(t_server *s, t_user *u, int stone)
{
  char	buffer[512];

  memset(buffer, '\0', 512);
  sprintf(buffer, DO_TAKE, u->fd, stone);
  safe_write_to_clients(s->gc_list, buffer);
  gc_do_inventory(s->gc_list, u);
  update_box_content(s, -1, u->y * s->option->width + u->x);
}

void	gc_do_die(t_user *gc_list, t_user *u)
{
  char	buffer[512];

  memset(buffer, '\0', 512);
  sprintf(buffer, DO_DIE, u->fd);
  safe_write_to_clients(gc_list, buffer);
}
