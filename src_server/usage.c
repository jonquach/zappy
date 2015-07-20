/*
** usage.c for  in /home/kauch_j/rendu/Zappy/src_server
** 
** Made by jonathan kauch
** Login   <kauch_j@epitech.net>
** 
** Started on  Thu Jul  2 13:20:24 2015 jonathan kauch
** Last update Thu Jul  2 13:20:54 2015 jonathan kauch
*/

#include <stdio.h>
#include "server.h"

int	usage(char *str)
{
  fprintf(stderr, "[Usage] : %s -p [PORT] -x [WIDTH] -y [HEIGHT]", str);
  fprintf(stderr, " -n [team name 1] [team name 2] [...]");
  fprintf(stderr, " -c [number of client] -t [time delay]\n");
  return (0);
}
