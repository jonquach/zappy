/*
** add_player.c for qsd in /home/quach_a/backupzappy/Zappy/src_server
** 
** Made by Jonathan Quach
** Login  <jonathan.quach@epitech.eu>
** 
** Started on  Sun Jul  5 20:58:06 2015 Jonathan Quach
** Last update Sun Jul  5 20:58:06 2015 Jonathan Quach
*/

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include "server.h"

void			add_to_users(t_server *s, int fd)
{
  t_user		*new;
  t_user		*new_user_list;

  if ((new = malloc(sizeof(*new))) == NULL)
    printstr(2, "Error: malloc\n");
  if ((new_user_list = malloc(sizeof(*new))) == NULL)
    printstr(2, "Error: malloc\n");
  motd(fd);
  new->fd = fd;
  new->level = 1;
  new->id = s->nb;
  new->food = 1000000 * (126 * 10 / s->option->exec_time);
  new->food_time = s->global_time;
  new->start = 1;
  new->direction = RIGHT;
  new->state = ACTIVE;
  new->x_incantation = -1;
  new->y_incantation = -1;
  new->stone_list = malloc_stone_list(10);
  new->input = malloc_input_list();
  new->next = s->users;
  s->users = new;
  s->nb++;
}

void                    create_ghost(t_server *s, t_user *user)
{
  t_user    *new;

  if (s->other_size > 99)
    return;
  if ((new = malloc(sizeof(*new))) == NULL)
    printstr(2, "Error: malloc\n");
  new->fd = s->id_egg;
  new->start = 1;
  new->level = user->level;
  new->direction = user->direction;
  new->state = GHOST;
  new->x = user->x;
  new->y = user->y;
  new->x_incantation = user->x_incantation;
  new->y_incantation = user->y_incantation;
  new->used = 0;
  new->global_time = s->global_time;
  new->team_name = user->team_name;
  new->stone_list = malloc_stone_list(10);
  new->next = s->other;
  new->food = 1000000 * (126 * 10 / s->option->exec_time);
  new->food_time = s->global_time;
  s->other = new;
  printf("**** Ghost created at (%d, %d)\n", new->x, new->y);
}

void			add_egg_in_list(t_server *s,
					char *name, int x, int y)
{
  t_user		*new;

  if (s->other_size > 299)
    return;
  if ((new = malloc(sizeof(*new))) == NULL)
    printstr(2, "Error: malloc\n");
  new->fd = s->id_egg;
  new->start = 1;
  new->level = 1;
  new->direction = RIGHT;
  new->state = EGG;
  new->x = x;
  new->y = y;
  new->x_incantation = -1;
  new->y_incantation = -1;
  new->used = 0;
  new->global_time = s->global_time;
  new->team_name = name;
  new->stone_list = malloc_stone_list(10);
  new->next = s->other;
  new->food = 1000000 * (126 * 10 / s->option->exec_time);
  new->food_time = s->global_time;
  s->other = new;
  ++s->id_egg;
  printf("**** Fork new player at (%d, %d)\n", x, y);
}

int			new_client(t_server *s)
{
  int			fd;
  struct sockaddr_in	s_in_client;
  socklen_t		s_in_size;

  s_in_size = sizeof(s_in_client);
  fd = accept(s->sock, (struct sockaddr *)&s_in_client, &s_in_size);
  if (fd == -1)
    printstr(2, "Error: accept\n");
  add_to_users(s, fd);
  return (1);
}
