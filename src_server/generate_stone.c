/*
** generate_stone.c for qsd in /home/quach_a/backupzappy/Zappy/src_server
** 
** Made by Jonathan Quach
** Login  <jonathan.quach@epitech.eu>
** 
** Started on  Sun Jul  5 20:57:26 2015 Jonathan Quach
** Last update Sun Jul  5 20:57:27 2015 Jonathan Quach
*/

#include <stdlib.h>
#include "server.h"
#include "protocol.h"

void	generate_stone(t_server *s, int stone, int nb_stone, int map_size)
{
  int	pos;

  while (nb_stone > 0)
    {
      pos = rand() % map_size;
      s->map[pos].stone_list[stone].nb++;
      --nb_stone;
    }
}

void	generate_food(t_server *s)
{
  int	pos;
  int	map_size;
  int	nb;

  map_size = s->option->width * s->option->height;
  nb = (double)map_size / 20;
  while (nb > 0)
    {
      pos = rand() % map_size;
      s->map[pos].stone_list[0].nb++;
      update_box_content(s, -1, pos);
      --nb;
    }
}
