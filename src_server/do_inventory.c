/*
** do_inventory.c for qsd in /home/quach_a/backupzappy/Zappy/src_server
** 
** Made by Jonathan Quach
** Login  <jonathan.quach@epitech.eu>
** 
** Started on  Sun Jul  5 20:58:25 2015 Jonathan Quach
** Last update Sun Jul  5 21:25:32 2015 Christophe Fraysse
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "server.h"
#include "protocol.h"

t_bool		do_inventory(t_server *s, t_user *user, char *buff)
{
  char		msg[4096];
  char		msg2[1024];

  (void)buff;
  memset(msg, 0, BUFFER_SIZE);
  memset(msg2, 0, BUFFER_SIZE);
  puts(user->stone_list[0].name);
  sprintf(msg, "{nourriture %d, linemate %d, deraumere %d,",
  	  user->stone_list[0].nb, user->stone_list[1].nb,
	  user->stone_list[2].nb);
  sprintf(msg2, " sibur %d, mendiane %d, phiras %d, thystame %d}\n",
  	  user->stone_list[3].nb, user->stone_list[4].nb,
	  user->stone_list[5].nb, user->stone_list[6].nb);
  strcat(msg, msg2);
  safe_write(user->fd, strlen(msg), msg);
  gc_do_inventory(s->gc_list, user);
  return (true);
}
