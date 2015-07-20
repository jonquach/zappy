/*
** send.c for qsd in /home/quach_a/backupzappy/Zappy/src_server
** 
** Made by Jonathan Quach
** Login  <jonathan.quach@epitech.eu>
** 
** Started on  Sun Jul  5 20:56:54 2015 Jonathan Quach
** Last update Sun Jul  5 20:56:55 2015 Jonathan Quach
*/

#include "server.h"

void	send_ok(int fd)
{
  safe_write(fd, 3, "ok\n");
}

void	send_ko(int fd)
{
  safe_write(fd, 3, "ko\n");
}
