/*
** init.c for qsd in /home/quach_a/backupzappy/Zappy/src_server
** 
** Made by Jonathan Quach
** Login  <jonathan.quach@epitech.eu>
** 
** Started on  Sun Jul  5 20:58:38 2015 Jonathan Quach
** Last update Sun Jul  5 21:28:10 2015 Christophe Fraysse
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include "server.h"

int			init_server(int port)
{
  int			sock;
  struct protoent	*pro;
  struct sockaddr_in	sin;
  int			maxcon;

  if ((maxcon = get_max_con()) == -1)
    return (-1);
  if ((pro = getprotobyname("TCP")) == 0)
    printstr(2, "Error: getprotobyname\n");
  if ((sock = socket(AF_INET, SOCK_STREAM, pro->p_proto)) == -1)
    printstr(2, "Error: socket\n");
  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);
  sin.sin_addr.s_addr = INADDR_ANY;
  set_socket_reuse(sock);
  if (bind(sock, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
    {
      xclose(sock);
      printstr(2, "Error: bind\n");
    }
  if (listen(sock, maxcon) == -1)
    xclose(sock);
  return (sock);
}

t_bool			init_team(t_server *serv, int nb_client,
				  char **team_name)
{
  int			i;

  i = 0;
  serv->nb = 0;
  if ((serv->team = malloc(sizeof(t_team) * nb_client)) == NULL)
    printstr(2, "Error : malloc\n");
  while (team_name[i] != NULL)
    {
      serv->team[i].name = team_name[i];
      serv->team[i].nb = nb_client;
      ++i;
    }
  return (true);
}

t_bool			init_map(t_server *serv, int width, int height)
{
  int			i;
  int			j;
  int			k;

  i = 0;
  j = 0;
  k = 0;
  if ((serv->map = malloc(sizeof(t_map) * (width * height))) == NULL)
    printstr(2, "Error : malloc\n");
  while (i < (width * height))
    {
      if (j == width)
	{
	  j = 0;
	  ++k;
	}
      serv->map[i].x = j;
      serv->map[i].y = k;
      serv->map[i].stone_list = malloc_stone_list(0);
      serv->map[i].user_list = NULL;
      ++i;
      ++j;
    }
  printf("**** Generating world... DONE !\n");
  return (true);
}

void			init_stone(t_server *serv, int map_size)
{
  double		quantity;

  quantity = (double)map_size / 10;
  if (quantity < 1)
    quantity = 1;
  generate_stone(serv, 0, 21 * quantity, map_size);
  generate_stone(serv, 1, 9 * quantity, map_size);
  generate_stone(serv, 2, 8 * quantity, map_size);
  generate_stone(serv, 3, 10 * quantity, map_size);
  generate_stone(serv, 4, 5 * quantity, map_size);
  generate_stone(serv, 5, 6 * quantity, map_size);
  generate_stone(serv, 6, 1 * quantity, map_size);
}
