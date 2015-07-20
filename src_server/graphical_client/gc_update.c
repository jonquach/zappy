/*
** gc_update.c for qsd in /home/quach_a/backupzappy/Zappy/src_server/graphical_client
** 
** Made by Jonathan Quach
** Login  <jonathan.quach@epitech.eu>
** 
** Started on  Sun Jul  5 20:59:12 2015 Jonathan Quach
** Last update Sun Jul  5 20:59:12 2015 Jonathan Quach
*/

#include <string.h>
#include <stdio.h>
#include "server.h"
#include "protocol.h"
#include "toolbox.h"

void		update_box_content(t_server *s, int fd, int pos)
{
  char		buffer[512];

  memset(buffer, '\0', 512);
  sprintf(buffer, BOX_CONTENT, s->map[pos].x, s->map[pos].y,
	  s->map[pos].stone_list[0].nb, s->map[pos].stone_list[1].nb,
	  s->map[pos].stone_list[2].nb, s->map[pos].stone_list[3].nb,
	  s->map[pos].stone_list[4].nb, s->map[pos].stone_list[5].nb,
	  s->map[pos].stone_list[6].nb);
  if (fd == -1)
    safe_write_to_clients(s->gc_list, buffer);
  else
    safe_write(fd, strlen(buffer), buffer);
}

void		update_game_time(t_server *s, int fd)
{
  char		buffer[512];

  memset(buffer, '\0', 512);
  sprintf(buffer, SET_GAME_TIME, (int)s->option->exec_time);
  if (fd == -1)
    safe_write_to_clients(s->gc_list, buffer);
  else
    safe_write(fd, strlen(buffer), buffer);
}
