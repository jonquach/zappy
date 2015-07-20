/*
** cmd.h for qsd in /home/quach_a/backupzappy/Zappy/inc
** 
** Made by Jonathan Quach
** Login  <jonathan.quach@epitech.eu>
** 
** Started on  Sun Jul  5 21:00:15 2015 Jonathan Quach
** Last update Sun Jul  5 21:00:16 2015 Jonathan Quach
*/

#ifndef CMD_H_
# define CMD_H_

static t_cmd	g_cmd[] =
  {
    {AVANCE, 6, 7, &do_go_forward},
    {DROITE, 6, 7, &do_turn_right},
    {GAUCHE, 6, 7, &do_turn_left},
    {VOIR, 4, 7, &do_see},
    {INVENTAIRE, 10, 7, &do_inventory},
    {TAKE, 5, 7, &do_take},
    {PUT, 4, 7, &do_put},
    {KICK, 7, 7, &do_kick},
    {BROADCAST, 9, 7, &do_broadcast},
    {INCANT, 11, 0, &do_check_incantation},
    {FORK, 4, 42, &do_fork},
    {CONNECT, 11, 0, &do_connect},
    {MORT, 1, 0, &do_die}
  };

#endif /* !CMD_H_ */
