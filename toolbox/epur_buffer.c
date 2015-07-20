/*
** epur_buffer.c for qsd in /home/frayss_c/tmp_zappy/Zappy/toolbox
** 
** Made by Christophe Fraysse
** Login   <frayss_c@epitech.net>
** 
** Started on  Sun Jul  5 22:41:41 2015 Christophe Fraysse
** Last update Sun Jul  5 22:41:42 2015 Christophe Fraysse
*/

#include <stdlib.h>
#include "toolbox.h"

void	epur_buffer(char *buffer, char *delim)
{
  int	i;
  int	j;

  i = 0;
  j = 0;
  if (buffer == NULL || delim == NULL)
    return;
  while (find_char_from_str(buffer[i], delim) == 0)
    ++i;
  while (buffer[i] != '\0')
    {
      while (find_char_from_str(buffer[i], delim) == -1)
	buffer[j++] = buffer[i++];
      while (find_char_from_str(buffer[i], delim) == 0)
	++i;
      if (buffer[i] != '\0')
	buffer[j++] = ' ';
    }
  while (buffer[j] != '\0')
    buffer[j++] = '\0';
}
