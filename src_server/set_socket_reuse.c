/*
** set_socket_reuse.c for qsd in /home/quach_a/backupzappy/Zappy/src_server
** 
** Made by Jonathan Quach
** Login  <jonathan.quach@epitech.eu>
** 
** Started on  Sun Jul  5 20:58:48 2015 Jonathan Quach
** Last update Sun Jul  5 20:58:48 2015 Jonathan Quach
*/

#include <sys/types.h>
#include <sys/socket.h>
#include "server.h"

void		set_socket_reuse(int sock)
{
  int		yes;

  yes = 1;
  if (setsockopt(sock, SOL_SOCKET,
                 SO_REUSEADDR, &yes, sizeof(int)) == -1)
    {
      xclose(sock);
      printstr(2, "Error: setsockopt\n");
    }
}
