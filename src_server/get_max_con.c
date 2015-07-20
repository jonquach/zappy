/*
** get_max_con.c for qsd in /home/quach_a/backupzappy/Zappy/src_server
** 
** Made by Jonathan Quach
** Login  <jonathan.quach@epitech.eu>
** 
** Started on  Sun Jul  5 20:57:24 2015 Jonathan Quach
** Last update Sun Jul  5 20:57:25 2015 Jonathan Quach
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "toolbox.h"

int		get_max_con()
{
  FILE		*ret;
  char		buff[42];
  int		val;

  memset(buff, 0, sizeof(buff));
  if ((ret = fopen("/proc/sys/net/core/somaxconn", "r")) == NULL)
    return (display_error("Could not open the somaxconn file.\n"));
  if (fgets(buff, sizeof(buff), ret) == NULL)
    return (display_error("Could not get the string file.\n"));
  fclose(ret);
  if (buff != NULL && (val = atoi(buff)) > 0)
    return (val);
  return (-1);
}
