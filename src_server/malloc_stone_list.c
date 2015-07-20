/*
** malloc_stone_list.c for putin in /home/quach_a/backupzappy/Zappy/src_server
** 
** Made by Jonathan Quach
** Login  <jonathan.quach@epitech.eu>
** 
** Started on  Sun Jul  5 20:57:03 2015 Jonathan Quach
** Last update Sun Jul  5 20:57:03 2015 Jonathan Quach
*/

#include <stdlib.h>
#include "server.h"

t_stone			*malloc_stone_list(int nb)
{
  t_stone		*stone_list;

  if ((stone_list = malloc(sizeof(t_stone) * 7)) == NULL)
    printstr(2, "Error : malloc\n");
  stone_list[0].nb = nb;
  stone_list[1].nb = 0;
  stone_list[2].nb = 0;
  stone_list[3].nb = 0;
  stone_list[4].nb = 0;
  stone_list[5].nb = 0;
  stone_list[6].nb = 0;
  stone_list[0].name = "nourriture";
  stone_list[1].name = "linemate";
  stone_list[2].name = "deraumere";
  stone_list[3].name = "sibur";
  stone_list[4].name = "mendiane";
  stone_list[5].name = "phiras";
  stone_list[6].name = "thystame";
  return (stone_list);
}
