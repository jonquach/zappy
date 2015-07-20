/*
** server.h for qsd in /home/quach_a/backupzappy/Zappy/inc
** 
** Made by Jonathan Quach
** Login  <jonathan.quach@epitech.eu>
** 
** Started on  Sun Jul  5 21:00:13 2015 Jonathan Quach
** Last update Sun Jul  5 22:05:21 2015 Christophe Fraysse
*/

#ifndef		SERVER_H_
# define	SERVER_H_

# include <sys/select.h>
# include <time.h>
# include "define.h"
# include "toolbox.h"

typedef enum		s_direction
{
  RIGHT = 1,
  DOWN = 2,
  LEFT = 3,
  UP = 4
}			e_direction;

typedef enum		s_msg_dir
{
  NONE = 0,
  MSG_UP = 1,
  MSG_UP_LEFT = 2,
  MSG_LEFT = 3,
  MSG_DOWN_LEFT = 4,
  MSG_DOWN = 5,
  MSG_DOWN_RIGHT = 6,
  MSG_RIGHT = 7,
  MSG_UP_RIGHT = 8
}			e_msg_dir;

typedef enum		s_state
{
    GHOST = 0,
    EGG,
    ACTIVE
}			e_state;

typedef	struct		s_args
{
  int			flags;
  int			port;
  int			width;
  int			height;
  char			**team_name;
  int			nb_client;
  double		exec_time;
}			t_args;

typedef struct		s_stone
{
  char			*name;
  int			nb;
}			t_stone;

typedef struct		s_input	t_input;

typedef struct		s_user
{
  int			fd;
  int			level;
  int			used;
  int			id;
  int			start;
  int			x;
  int			y;
  int			x_incantation;
  int			y_incantation;
  double		global_time;
  double		food;
  double		food_time;
  char			*team_name;
  t_stone		*stone_list;
  t_input		*input;
  e_direction		direction;
  e_state		state;
  struct s_user		*next;
}			t_user;

typedef struct		s_team
{
  char			*name;
  int			nb;
}			t_team;

typedef struct		s_map
{
  int			x;
  int			y;
  t_user		*user_list;
  t_stone		*stone_list;
}			t_map;

typedef struct		s_server
{
  t_bool		err;
  int			nb;
  int			id_egg;
  int			sock;
  fd_set		readfds;
  int			max_fd;
  double		global_time;
  int			other_size;
  t_team		*team;
  t_args		*option;
  t_user		*users;
  t_user		*queue;
  t_user		*gc_list;
  t_user		*other;
  t_map			*map;
}			t_server;

typedef struct		s_cmd
{
  char			*name;
  int			lenght;
  double		delay;
  t_bool		(*func)(t_server *, t_user *, char *);
}			t_cmd;

typedef struct		s_input
{
  t_cmd			*cmd;
  char			*buffer;
  int			global_time;
  struct s_input	*prev;
  struct s_input	*next;
}			t_input;

typedef struct		s_recipe
{
  int			player_nb;
  char			*stone_combi;
}			t_recipe;

/*
** main.c
*/
t_bool		check_args(int, char **, t_args *);

/*
** check_args.c
*/
int		is_port(int);
int		check_dimension(int);
int		get_team_name(t_args *, char **);
t_bool		check_part_one(int, char **, t_args *);
t_bool		check_part_two(int, char **, t_args *);

/*
** check_other_list.c
*/
t_bool		check_other_list(t_server *, t_user *);

/*
** do_broadcast.c
*/
t_bool		do_broadcast(t_server *, t_user *, char *);

/*
** do_broadcast_fuc.c
*/
char		*split_buffer(char *);
int		calc_dir(t_user *, e_msg_dir);

/*
** do_fork.c
*/
t_bool		do_fork(t_server *, t_user *, char *);

/*
** do_die.c
*/
t_bool		do_die(t_server *, t_user *, char *);

/*
** do_incantation.c
*/
void		level_up_player_at_pos(t_server *, int, int, int);
t_bool		remove_stone_combi_at_pos(t_server *, t_map *, char *);
void		set_incantation_pos(t_server *, int, int, int);
t_bool		do_incantation_ko(t_server *, t_user *, char *);
t_bool		do_incantation(t_server *, t_user *, char *);

/*
** do_check_incantation.c
*/
void		add_incantation_to_input_list(t_server *, t_input **, char *);
t_bool		do_check_incantation(t_server *, t_user *, char *);

/*
** init.c
*/
int		init_server(int);
t_bool		init_map(t_server *, int, int);
t_bool		init_team(t_server *, int, char **);
void		init_stone(t_server *, int);

/*
** set_socket_reuse.c
*/
void		set_socket_reuse(int);

/*
** server_loop.c
*/
void		aff(t_server *);
t_bool		server_loop(t_server *);
t_bool		into_loop(t_server *);
t_bool		send_information(t_server *, int);
void		reset_stone_list(t_stone *);

/*
** fds.c
*/
void		set_fd(int, t_server *);
void		set_all_fds(t_server *);
void		reset_fds(t_server *);

/*
** write_to_clients.c
*/
void		write_to_clients(t_server *, t_user *, char *);
void		safe_write_to_clients(t_user *, char *);

/*
** write_exit.c
*/
void		write_exit(int);

/*
** check_team.c
*/
t_bool		check_if_team_exist(char **, char *);
char		*check_team_name(char **, char *);
t_bool		decrement_nb_of_team(t_server *, char *);
t_bool		add_team_name_to_user(t_server *, char *, int);

/*
** check_team.c
*/
t_bool		check_this_team_name(char *, t_args *);
t_bool		check_multiple_team_name(t_args *);

/*
** list_del_elem_at_position.c
*/
t_bool		list_del_elem_at_position(t_user **, int);
t_bool		list_del_elem_at_position_no_close(t_user **, int);
t_bool		list_del_egg_at_position_no_close(t_user **, int);
t_bool		list_del_used_at_position_no_close(t_user **, int);

/*
** put_in_the_queue.c
*/
void		put_in_the_queue(t_server *, char *, int);

/*
** add_player.c
*/
void		add_to_users(t_server *, int);
int		new_client(t_server *s);
void		add_egg_in_list(t_server *, char *, int, int);
void		create_ghost(t_server *, t_user *);

/*
** check_cmd.c
*/
t_bool		check_cmd(t_server *, t_user *, char *);
t_bool		do_go_forward(t_server *, t_user *, char *);
t_bool		do_turn_left(t_server *, t_user *, char *);
t_bool		do_turn_right(t_server *, t_user *, char *);
t_bool		do_inventory(t_server *, t_user *, char *);
t_bool		do_take(t_server *, t_user *, char *);
t_bool		do_put(t_server *, t_user *, char *);
t_bool		do_kick(t_server *, t_user *, char *);
t_bool		do_fork(t_server *, t_user *, char *);
t_bool		do_connect(t_server *, t_user *, char *);
t_bool		do_die(t_server *, t_user *, char *);

/*
** do_see.c
*/
t_bool		do_see(t_server *, t_user *, char *);

/*
** do_see_func.c
*/
int		set_tmp_coord(int, int);


/*
** do_incantation.c
*/
t_bool		do_incantation(t_server *, t_user *, char *);
t_bool    do_incantation_ko(t_server *, t_user *, char *);
t_bool		do_check_incantation(t_server *, t_user *, char *);

/*
** get_map_at_pos.c
*/
t_bool		get_player_at_pos(t_map *, t_user *, int, t_bool);
t_bool		get_stone_combi_at_pos(t_map *, char *, t_bool);
void		get_map_at_pos(t_map *, char *);

/*
** get_max_con.c
*/

int		get_max_con();

/*
** send.c
*/
void		send_ok(int);
void		send_ko(int);

/*
** check_read.c
*/
void		check_read(t_server *, t_user *);

/*
** check_isset_read.c
*/
void		check_isset_read(t_server *);

/*
** check_winner.c
*/
t_bool		check_winner(t_server *);

/*
** disconnect_client.c
*/
void		disconnect(t_server *, t_user *);

/*
** motd.c
*/
void		motd(int);

/*
** display_init.c
*/
void		display_init(t_args *);

/*
** add_remove_player.c
*/
t_bool		delete_user_of_map(t_server *, t_user *);
t_bool		delete_egg_of_map(t_server *, t_user *);
t_bool		add_user_in_the_map(t_server *, t_user *);
t_bool		add_egg_in_the_map(t_server *, t_user *);
t_bool		update_to_user_list(t_server *, t_user *);

/*
** delete_them.c
*/
void		delete_them(t_server *, t_user *, int);

/*
** malloc_stone_list.c
*/
t_stone		*malloc_stone_list(int);

/*
** add_to_graphic_team.c
*/
t_bool		add_to_graphic_team(t_server *, char *, int);

/*
** input_list_func.c
*/
t_input		*malloc_input_list();
t_bool		check_input_list_size(t_input **);
void		push_back_input_list(t_server *, t_input **, int, char *);
t_bool		pop_front_input_list(t_input **);

/*
** input_list_queue.c
*/
void		check_input_list(t_server *, t_user *);
t_bool		is_input_list_empty(t_server *, t_user *, int, char *);

/*
** free_list.c
*/
void		free_list(t_user *, t_bool);
void		free_list_input(t_input *);

/*
** remove_all.c
*/
void		remove_all(t_server *);

/*
** usage.c
*/
int		usage(char *);

/*
** generate_stone.c
*/
void		generate_stone(t_server *, int, int, int);
void		generate_food(t_server *);

/*
** assigns_coord.c
*/
void		assigns_coord(t_server *, t_user **);

#endif /* !SERVER_H_ */
