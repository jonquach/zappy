/*
** xclose.c for  in /home/frayss_c/tmp_zappy/Zappy/toolbox
** 
** Made by Christophe Fraysse
** Login   <frayss_c@epitech.net>
** 
** Started on  Sun Jul  5 22:27:56 2015 Christophe Fraysse
** Last update Sun Jul  5 22:28:14 2015 Christophe Fraysse
*/

#include <unistd.h>
#include <stdlib.h>
#include "toolbox.h"

void	xclose(int fd)
{
  if (close(fd) == -1)
    printstr(2, "Error : close");
}
