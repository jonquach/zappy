/*
** find_char_from_str.c for qsd$ in /home/frayss_c/tmp_zappy/Zappy/toolbox
** 
** Made by Christophe Fraysse
** Login   <frayss_c@epitech.net>
** 
** Started on  Sun Jul  5 22:42:59 2015 Christophe Fraysse
** Last update Sun Jul  5 22:43:05 2015 Christophe Fraysse
*/

#include <stdlib.h>

int	find_char_from_str(char c, char *str)
{
  int	i;

  i = 0;
  if (c == '\0' || str == NULL)
    return (-1);
  while (str[i] != '\0')
    {
      if (str[i] == c)
	return (0);
      ++i;
    }
  return (-1);
}
