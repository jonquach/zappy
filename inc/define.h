/*
** define.h for qsd in /home/quach_a/backupzappy/Zappy/inc
** 
** Made by Jonathan Quach
** Login  <jonathan.quach@epitech.eu>
** 
** Started on  Sun Jul  5 21:00:20 2015 Jonathan Quach
** Last update Sun Jul  5 21:00:21 2015 Jonathan Quach
*/

#ifndef		DEFINE_H_
# define	DEFINE_H_

# define PROTOCOL "TCP"
# define BUFFER_SIZE 4096
# define WELCOME "BIENVENUE\n"

/*
** COMMANDE
*/
# define AVANCE "avance"
# define DROITE "droite"
# define GAUCHE "gauche"
# define VOIR "voir"
# define INVENTAIRE "inventaire"
# define TAKE "prend"
# define PUT "pose"
# define KICK "expulse"
# define BROADCAST "broadcast"
# define INCANT "incantation"
# define FORK "fork"
# define CONNECT "connect_nbr"
# define MORT "-"
# define SHOW "show"

typedef	enum	e_bool
  {
    false,
    true
  }		t_bool;

#endif	/* !DEFINE_H_ */
