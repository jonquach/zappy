/*
** check_read.c for qsd in /home/quach_a/backupzappy/Zappy/src_server
** 
** Made by Jonathan Quach
** Login  <jonathan.quach@epitech.eu>
** 
** Started on  Sun Jul  5 20:58:13 2015 Jonathan Quach
** Last update Sun Jul  5 20:58:13 2015 Jonathan Quach
*/

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "server.h"

void		check_read(t_server *serv, t_user *writer)
{
  char		buf[BUFFER_SIZE];
  int		ret;

  memset(buf, 0, BUFFER_SIZE);
  ret = 0;
  ret = read(writer->fd, buf, BUFFER_SIZE);
  if (ret > 0)
    {
      buf[ret - 1] = 0;
      if (check_cmd(serv, writer, buf) == false)
        send_ko(writer->fd);
    }
  else if (ret <= 0)
    disconnect(serv, writer);
}
