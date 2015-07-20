/*
** free_wordtab.c for  in /home/frayss_c/tmp_zappy/Zappy/toolbox
** 
** Made by Christophe Fraysse
** Login   <frayss_c@epitech.net>
** 
** Started on  Sun Jul  5 22:30:55 2015 Christophe Fraysse
** Last update Sun Jul  5 22:30:56 2015 Christophe Fraysse
*/

#include <stdlib.h>
#include "toolbox.h"

void	free_wordtab(char **tab)
{
  void	*tmp;

  if (tab == NULL)
    return;
  tmp = tab;
  while (*tab != NULL)
    {
      free(*tab);
      ++tab;
    }
  free(tmp);
}
