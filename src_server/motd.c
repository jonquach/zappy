/*
** motd.c for qsd in /home/quach_a/backupzappy/Zappy/src_server
** 
** Made by Jonathan Quach
** Login  <jonathan.quach@epitech.eu>
** 
** Started on  Sun Jul  5 20:58:43 2015 Jonathan Quach
** Last update Sun Jul  5 20:58:44 2015 Jonathan Quach
*/

#include <string.h>
#include "server.h"

void	motd(int fd)
{
  char	msg[BUFFER_SIZE];

  memset(msg, 0, BUFFER_SIZE);
  strcat(msg, WELCOME);
  printstr(fd, msg);
}
