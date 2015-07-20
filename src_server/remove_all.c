/*
** remove_all.c for qsd in /home/quach_a/backupzappy/Zappy/src_server
** 
** Made by Jonathan Quach
** Login  <jonathan.quach@epitech.eu>
** 
** Started on  Sun Jul  5 20:56:56 2015 Jonathan Quach
** Last update Sun Jul  5 20:56:57 2015 Jonathan Quach
*/

#include <unistd.h>
#include <stdio.h>
#include "server.h"

void      remove_all(t_server *s)
{
  int     i;
  t_user   *tmp;

  i = 0;
  tmp = s->users;
  while (tmp != NULL)
  {
    do_die(s, tmp, NULL);
    free_list_input(tmp->input);
    tmp = tmp->next;
  }
  free_list(s->users, true);
  free_list(s->other, false);
  while (i < s->option->width * s->option->height)
  {
    free_list(s->map[i].user_list, false);
    reset_stone_list(s->map[i].stone_list);
    ++i;
  }
}
