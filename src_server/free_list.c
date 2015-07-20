/*
** free_list.c for qsd in /home/quach_a/backupzappy/Zappy/src_server
** 
** Made by Jonathan Quach
** Login  <jonathan.quach@epitech.eu>
** 
** Started on  Sun Jul  5 20:58:31 2015 Jonathan Quach
** Last update Sun Jul  5 20:58:32 2015 Jonathan Quach
*/

#include <stdlib.h>
#include "server.h"

void		free_list(t_user *head, t_bool option)
{
  t_user	*tmp;

  while (head != NULL)
    {
      tmp = head;
      if (option == true)
	xclose(head->fd);
      head = head->next;
      free(tmp);
    }
}

void		free_list_input(t_input *head)
{
  t_input	*tmp;

  while (head != NULL)
    {
      tmp = head;
      head = head->next;
      free(tmp);
    }
}
