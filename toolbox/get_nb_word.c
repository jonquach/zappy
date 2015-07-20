/*
** get_nb_word.c for qsd$ in /home/frayss_c/tmp_zappy/Zappy/toolbox
** 
** Made by Christophe Fraysse
** Login   <frayss_c@epitech.net>
** 
** Started on  Sun Jul  5 22:44:18 2015 Christophe Fraysse
** Last update Sun Jul  5 22:44:19 2015 Christophe Fraysse
*/

#include <stdlib.h>
#include "toolbox.h"

int	get_nb_word(char *str, char *delim)
{
  int	i;
  int	nb_word;

  i = 0;
  nb_word = 1;
  if (str == NULL)
    return (0);
  if (str[0] == '\0')
    return (0);
  while (str[i] != '\0')
    {
      if (find_char_from_str(str[i], delim) == 0)
	++nb_word;
      ++i;
    }
  return (nb_word);
}
