/*
** check_team_name.c for qsd in /home/quach_a/backupzappy/Zappy/src_server
** 
** Made by Jonathan Quach
** Login  <jonathan.quach@epitech.eu>
** 
** Started on  Sun Jul  5 20:58:14 2015 Jonathan Quach
** Last update Sun Jul  5 20:58:15 2015 Jonathan Quach
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "server.h"

t_bool check_this_team_name(char *str, t_args *opt)
{
  int i;
  int j;

  i = 0;
  j = 0;
  while (opt->team_name && opt->team_name[i])
  {
    if (strcmp(str, opt->team_name[i]) == 0)
      ++j;
    ++i;
  }
  if (j >= 2)
    return (false);
  return (true);
}

t_bool check_multiple_team_name(t_args *opt)
{
  int i;

  i = 0;
  while (opt->team_name && opt->team_name[i])
  {
    if (check_this_team_name(opt->team_name[i], opt) == false)
    {
      fprintf(stderr, "Error : each team name must be unique\n");
      return (false);
    }
    ++i;
  }
  return (true);
}
