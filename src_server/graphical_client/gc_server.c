/*
** gc_server.c for qsd in /home/quach_a/backupzappy/Zappy/src_server/graphical_client
** 
** Made by Jonathan Quach
** Login  <jonathan.quach@epitech.eu>
** 
** Started on  Sun Jul  5 20:59:13 2015 Jonathan Quach
** Last update Sun Jul  5 20:59:14 2015 Jonathan Quach
*/

#include <string.h>
#include <stdio.h>
#include "server.h"
#include "protocol.h"

void	gc_end_game(t_user *gc_list, char *team_name)
{
  char	buffer[512];

  memset(buffer, '\0', 512);
  sprintf(buffer, END_GAME, team_name);
  safe_write_to_clients(gc_list, buffer);
}

void	gc_message(t_user *gc_list, char *msg)
{
  char	buffer[512];

  memset(buffer, '\0', 512);
  sprintf(buffer, MESSAGE, msg);
  safe_write_to_clients(gc_list, buffer);
}

void	gc_unknows_cmd(t_user *gc_list)
{
  safe_write_to_clients(gc_list, UNKNOWN_CMD);
}

void	gc_bad_params(t_user *gc_list)
{
  safe_write_to_clients(gc_list, BAD_PARAMS);
}
