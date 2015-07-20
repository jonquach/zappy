/*
** main.c for qsd in /home/quach_a/backupzappy/Zappy/src_server
** 
** Made by Jonathan Quach
** Login  <jonathan.quach@epitech.eu>
** 
** Started on  Sun Jul  5 20:58:41 2015 Jonathan Quach
** Last update Sun Jul  5 20:58:42 2015 Jonathan Quach
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <time.h>
#include "server.h"
#include "protocol.h"

t_server	g_s;

static t_bool	check_all_args(t_args *opt)
{
  int		i;

  i = 0;
  while (opt->team_name && opt->team_name[i])
    ++i;
  if (i < 2)
    return (false);
  if (check_multiple_team_name(opt) == false)
    return (false);
  if ((opt->flags < 4) || (opt->width == 0)
      || (opt->height == 0) || (opt->nb_client == 0))
    return (false);
  return (true);
}

static void	init_args(t_args *option)
{
  option->flags = 0;
  option->port = 4242;
  option->width = 0;
  option->height = 0;
  option->team_name = NULL;
  option->nb_client = 0;
  option->exec_time = 100;
}

void		signal_handler(int sig)
{
  if (sig == SIGINT)
    g_s.err = 1;
}

int		main(int ac, char **av)
{
  t_args	option;

  if (ac < 5)
    return (usage(av[0]));
  signal(SIGINT, &signal_handler);
  signal(SIGPIPE, SIG_IGN);
  srand(time(NULL) + getpid());
  init_args(&option);
  if (check_args(ac, av, &option) == false
      || check_all_args(&option) == false)
    return (usage(av[0]));
  display_init(&option);
  g_s.global_time = 0;
  g_s.id_egg = 1;
  g_s.other_size = 0;
  if ((g_s.sock = init_server(option.port)) == -1)
    return (display_error("Error : Could not init the server.\n"));
  printf("**** Initialization done\n");
  init_map(&g_s, option.width, option.height);
  init_team(&g_s, option.nb_client, option.team_name);
  init_stone(&g_s, option.width * option.height);
  g_s.option = &option;
  server_loop(&g_s);
  xclose(g_s.sock);
  return (0);
}
