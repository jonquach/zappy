##
## Makefile for qsd in /home/quach_a/backupzappy/Zappy
## 
## Made by Jonathan Quach
## Login  <jonathan.quach@epitech.eu>
## 
## Started on  Sun Jul  5 20:59:46 2015 Jonathan Quach
## Last update Sun Jul  5 22:56:51 2015 jonathan kauch
##

CC		=	gcc
CPP		=	g++

INCLUDE		=	inc/
SERVER_GC_DIR	=	src_server/graphical_client/

SRC_SERVER	=	src_server/add_player.c \
			src_server/add_to_graphic_team.c \
			src_server/add_remove_player.c \
			src_server/assigns_coord.c \
			src_server/check_args.c \
			src_server/check_cmd.c \
			src_server/check_isset_read.c \
			src_server/check_read.c \
			src_server/check_team.c \
			src_server/check_other_list.c \
			src_server/check_winner.c \
			src_server/check_team_name.c \
			src_server/connect_nbr.c \
			src_server/delete_them.c \
			src_server/disconnect_client.c \
			src_server/display_init.c \
			src_server/do_incantation.c \
			src_server/do_check_incantation.c \
			src_server/do_go_forward.c \
			src_server/do_broadcast.c \
			src_server/do_broadcast_func.c \
			src_server/do_inventory.c \
			src_server/do_fork.c \
			src_server/do_kick.c \
			src_server/do_die.c \
			src_server/do_see.c \
			src_server/do_see_func.c \
			src_server/do_take_put.c \
			src_server/do_turn.c \
			src_server/fds.c \
			src_server/free_list.c \
			src_server/generate_stone.c \
			src_server/get_map_at_pos.c \
			src_server/get_max_con.c \
			src_server/get_team_name.c \
			src_server/init.c \
			src_server/set_socket_reuse.c \
			src_server/list_del_elem_at_position.c \
			src_server/malloc_stone_list.c \
			src_server/motd.c \
			src_server/server_loop.c \
			src_server/input_list_func.c \
			src_server/input_list_queue.c \
			src_server/send.c \
			src_server/send_information.c \
			src_server/remove_all.c \
			src_server/reset_stone_list.c \
			src_server/usage.c \
			src_server/write_to_clients.c \
			src_server/main.c

SRC_SERVER_GC	=	$(SERVER_GC_DIR)gc_cmd1.c \
			$(SERVER_GC_DIR)gc_cmd2.c \
			$(SERVER_GC_DIR)gc_egg.c \
			$(SERVER_GC_DIR)gc_init.c \
			$(SERVER_GC_DIR)gc_player.c \
			$(SERVER_GC_DIR)gc_server.c \
			$(SERVER_GC_DIR)gc_update.c

SRC_CLIENT_CPP	=	src_client/ParseArg.cpp \
			src_client/Exception.cpp \
			src_client/Client.cpp \
			src_client/AI.cpp \
			src_client/Coord.cpp \
			src_client/GetToNextLvl.cpp \
			src_client/Teammate.cpp \
			src_client/Goal.cpp \
			src_client/Food.cpp \
			src_client/Command.cpp \
			src_client/Message.cpp \
			src_client/main.cpp

SRC_TOOLBOX	=	toolbox/epur_buffer.c \
			toolbox/find_char_from_str.c \
			toolbox/free_wordtab.c \
			toolbox/get_nb_word.c \
			toolbox/print.c \
			toolbox/str_to_wordtab.c \
			toolbox/xclose.c

ZAPPY_SERVER	=	zappy_server
ZAPPY_AI	=	zappy_ai

OBJ_SERVER	=	$(SRC_SERVER:.c=.o) \
			$(SRC_SERVER_GC:.c=.o) \
			$(SRC_TOOLBOX:.c=.o)

OBJ_AI		=	$(SRC_CLIENT_CPP:.cpp=.o)

CFLAGS		= 	-Wall -Wextra -Werror -I$(INCLUDE)
CPPFLAGS	= 	-Wall -Wextra -Werror -I$(INCLUDE)

RM		=	rm -f

all:			$(ZAPPY_AI) $(ZAPPY_SERVER)

$(ZAPPY_SERVER):	$(OBJ_SERVER)
			$(CC) $(OBJ_SERVER) -o $(ZAPPY_SERVER)

$(ZAPPY_AI):		$(OBJ_AI)
			$(CPP) $(OBJ_AI) -o $(ZAPPY_AI)

clean:
			$(RM) $(OBJ_SERVER) $(OBJ_AI) $(OBJ_TOOLBOX)

fclean:			clean
			$(RM) $(ZAPPY_SERVER) $(ZAPPY_AI)

re:			fclean all

.PHONY:			all clean fclean re
