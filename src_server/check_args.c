/*
** check_args.c for qsd in /home/quach_a/backupzappy/Zappy/src_server
** 
** Made by Jonathan Quach
** Login  <jonathan.quach@epitech.eu>
** 
** Started on  Sun Jul  5 20:58:09 2015 Jonathan Quach
** Last update Sun Jul  5 20:58:09 2015 Jonathan Quach
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "server.h"

int		is_port(int nb)
{
  if (nb > 1023 && nb <= 655355)
    return (nb);
  else
    return (-1);
}

int		check_dimension(int nb)
{
  if (nb >= 5 && nb <= 50)
    return (nb);
  else
    return (-1);
}

t_bool		check_part_one(int opt, char **av, t_args *option)
{
  if (opt == 'p')
    {
      if ((option->port = is_port(atoi(av[optind]))) == -1)
	return (false);
    }
  else if (opt == 'x')
    {
      if ((option->width = check_dimension(atoi(av[optind]))) == -1)
	return (false);
    }
  else if (opt == 'y')
    {
      if ((option->height = check_dimension(atoi(av[optind]))) == -1)
	return (false);
    }
  option->flags++;
  return (true);
}

t_bool		check_part_two(int opt, char **av, t_args *option)
{
  if (opt == 'n')
    optind += get_team_name(option, av + optind);
  else if (opt == 'c')
    {
      if ((option->nb_client = atoi(av[optind])) == 0)
	return (false);
    }
  else if (opt == 't')
    {
      if ((option->exec_time = atoi(av[optind])) == 0)
	return (false);
    }
  option->flags++;
  return (true);
}

t_bool		check_args(int ac, char **av, t_args *option)
{
  int		opt;

  while ((opt = getopt(ac, av, "pxynct")) != -1)
    {
      if (av[optind] == NULL)
	return (false);
      if (check_part_one(opt, av, option) == false)
	return (false);
      if (check_part_two(opt, av, option) == false)
	return (false);
    }
  return (true);
}
