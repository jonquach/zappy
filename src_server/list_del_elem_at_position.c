/*
** list_del_elem_at_position.c for qsd in /home/quach_a/backupzappy/Zappy/src_server
** 
** Made by Jonathan Quach
** Login  <jonathan.quach@epitech.eu>
** 
** Started on  Sun Jul  5 20:57:15 2015 Jonathan Quach
** Last update Sun Jul  5 20:57:16 2015 Jonathan Quach
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "server.h"

t_bool		list_del_elem_at_position(t_user **front_ptr, int fd)
{
  t_user	*current;
  t_user	*tmp_prev;

  tmp_prev = NULL;
  current = *front_ptr;
  while (current != NULL && current->fd != fd)
    {
      tmp_prev = current;
      current = current->next;
    }
  if (current == NULL)
    return (false);
  xclose(current->fd);
  if (tmp_prev != NULL)
    tmp_prev->next = current->next;
  else
    *front_ptr = current->next;
  free(current);
  return (true);
}

t_bool    list_del_elem_at_position_no_close(t_user **front_ptr, int fd)
{
  t_user  *current;
  t_user  *tmp_prev;

  tmp_prev = NULL;
  if (front_ptr == NULL)
    return (false);
  current = *front_ptr;
  while (current != NULL && current->fd != fd)
    {
      tmp_prev = current;
      current = current->next;
    }
  if (current == NULL)
    return (false);
  if (tmp_prev != NULL)
    tmp_prev->next = current->next;
  else
    *front_ptr = current->next;
  free(current);
  return (true);
}

t_bool    list_del_used_at_position_no_close(t_user **front_ptr, int fd)
{
  t_user  *current;
  t_user  *tmp_prev;

  tmp_prev = NULL;
  if (front_ptr == NULL)
    return (false);
  current = *front_ptr;
  while (current != NULL && current->fd != fd
	 && current->state == GHOST && current->used == 1)
    {
      tmp_prev = current;
      current = current->next;
    }
  if (current == NULL)
    return (false);
  if (tmp_prev != NULL)
    tmp_prev->next = current->next;
  else
      *front_ptr = current->next;
  free(current);
  return (true);
}

t_bool    list_del_egg_at_position_no_close(t_user **front_ptr, int fd)
{
  t_user  *current;
  t_user  *tmp_prev;

  tmp_prev = NULL;
  if (front_ptr == NULL)
    return (false);
  current = *front_ptr;
  while (current != NULL && current->fd != fd && current->state == GHOST)
    {
      tmp_prev = current;
      current = current->next;
    }
  if (current == NULL)
    return (false);
  if (tmp_prev != NULL)
    tmp_prev->next = current->next;
  else
      *front_ptr = current->next;
  free(current);
  return (true);
}
