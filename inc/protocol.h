/*
** protocol.h for qsd in /home/quach_a/backupzappy/Zappy/inc
** 
** Made by Jonathan Quach
** Login  <jonathan.quach@epitech.eu>
** 
** Started on  Sun Jul  5 21:00:14 2015 Jonathan Quach
** Last update Sun Jul  5 21:00:14 2015 Jonathan Quach
*/

#ifndef PROTOCOL_H_
# define PROTOCOL_H_

/*
** gc_init.c
*/
# define WELCOME "BIENVENUE\n"
# define MAP_SIZE "msz %d %d\n"
# define TEAM_NAME "tna %s\n"

void	gc_init(t_server *s, int fd);

/*
** gc_update.c : fd(-1) to send to gc_list
*/
# define BOX_CONTENT "bct %d %d %d %d %d %d %d %d %d\n"
# define SET_GAME_TIME "sgt %d\n"

void	update_box_content(t_server *s, int fd, int pos);
void	update_game_time(t_server *s, int fd);

/*
** gc_player.c : fd(-1) to send to gc_list
*/
# define NEW_PLAYER "pnw %d %d %d %d %d %s\n"
# define PLAYER_POS "ppo %d %d %d %d\n"
# define PLAYER_LEVEL "plv %d %d\n"

void	connect_new_player(t_user *gc_list, t_user *u, int fd);
void	update_player_pos(t_user *gc_list, t_user *u);
void	update_player_level(t_server *s, int x, int y, int level);

/*
** gc_cmd1.c
*/
# define DO_INVENTORY "pin %d %d %d %d %d %d %d %d %d %d\n"
# define DO_KICK "pex %d\n"
# define DO_BROADCAST "pbc %d %s\n"
# define DO_INCANTATION "pic %d %d %d %d\n"
# define END_INCANTATION "pie %d %d %s\n"

void	gc_do_inventory(t_user *gc_list, t_user *u);
void	gc_do_kick(t_user *gc_list, t_user *u);
void	gc_do_broadcast(t_user *gc_list, t_user *u, char *msg);
void	gc_do_incantation(t_server *s, int x, int y, int level);
void	gc_end_incantation(t_user *gc_list, int x, int y, char *result);

/*
** gc_cmd2.c
*/
# define DO_PUT "pdr %d %d\n"
# define DO_TAKE "pgt %d %d\n"
# define DO_DIE "pdi %d\n"

void	gc_do_take(t_server *s, t_user *u, int stone);
void	gc_do_put(t_server *s, t_user *u, int stone);
void	gc_do_die(t_user *gc_list, t_user *u);

/*
** gc_egg.c
*/
# define DO_FORK "pfk %d\n"
# define NEW_EGG "enw %d %d %d %d\n"
# define EGG_HATCH "eht %d\n"
# define CONNECT_PLAYER_TO_EGG "ebo %d\n"
# define EGG_DIEDEDED "edi %d\n"

void	gc_do_fork(t_user *gc_list, t_user *u, int fde);
void	gc_egg_hatch(t_user *gc_list, int fde);
void	connect_player_to_egg(t_user *gc_list, int fde);
void	gc_egg_die(t_user *gc_list, int fde);

/*
** gc_server.c
*/
# define END_GAME "seg %s\n"
# define MESSAGE "smg %s\n"
# define UNKNOWN_CMD "suc\n"
# define BAD_PARAMS "sbp\n"

void	gc_end_game(t_user *gc_list, char *team_name);
void	gc_message(t_user *gc_list, char *msg);
void	gc_unknows_cmd(t_user *gc_list);
void	gc_bad_params(t_user *gc_list);

#endif /* PROTOCOL_H_ */
