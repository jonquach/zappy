/*
** str_to_wordtab.c for  in /home/frayss_c/tmp_zappy/Zappy/toolbox
** 
** Made by Christophe Fraysse
** Login   <frayss_c@epitech.net>
** 
** Started on  Sun Jul  5 22:28:35 2015 Christophe Fraysse
** Last update Sun Jul  5 22:28:36 2015 Christophe Fraysse
*/

#include <stdlib.h>
#include <string.h>
#include "toolbox.h"

static char	*wordcpy(char *str, char *delim, int i)
{
  char		*word;
  int		j;

  j = i;
  while (find_char_from_str(str[j], delim) == -1 && str[j] != '\0')
    ++j;
  if ((word = malloc(sizeof(char) * (j - i + 1))) == NULL)
    printstr(2, "Error : malloc\n");
  j = 0;
  while (find_char_from_str(str[i], delim) == -1 && str[i] != '\0')
    {
      word[j] = str[i];
      ++i;
      ++j;
    }
  word[j] = '\0';
  return (word);
}

char		**str_to_wordtab(char *str, char *delim)
{
  char		**tab;
  int		i;
  int		j;

  if (str == NULL || delim == NULL)
    return (NULL);
  if ((tab = malloc(sizeof(char *) * (get_nb_word(str, delim) + 1))) == NULL)
    printstr(2, "Error : malloc\n");
  i = 0;
  j = 0;
  while (str[i] != '\0')
    {
      if (find_char_from_str(str[i], delim) == -1)
        {
          tab[j] = wordcpy(str, delim, i);
          i += strlen(tab[j++]);
        }
      else
        ++i;
    }
  tab[j] = NULL;
  return (tab);
}
