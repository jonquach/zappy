#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm> // remove
#include <cstring> // memset
#include <unistd.h> // close
#include <netdb.h> // getprotybyname
#include <sys/socket.h> // socket
#include <arpa/inet.h> // htons
#include <sys/types.h> // connect
#include <sys/socket.h> // connect
#include <sys/select.h> // select
#include <stdlib.h>
#include <time.h>
#include "Exception.hpp"
#include "Coord.hpp"
#include "Teammate.hpp"

class Client
{
public:
  enum e_item
    {
      FOOD,
      LINEMATE,
      DERAUMERE,
      SIBUR,
      MENDIANE,
      PHIRAS,
      THYSTAME
    };

  enum e_step
    {
      ERROR_STEP = -1,
      WELCOME_STEP = 0,
      DATA_STEP = 1,
      GAME_STEP = 2
    };

  enum e_command
    {
      NONE,
      BASIC,
      SEEK,
      LOOK,
      FORK,
      INVENTORY,
      INCANTATION,
      PICKUP
    };

  enum e_direction
    {
      NORTH,
      EAST,
      SOUTH,
      WEST
    };

private:
  int _port;
  std::string _ip;
  std::string _teamName;
  std::string _ans;
  std::vector<std::string> _items;
  std::vector<Coord> _view;
  std::vector<Teammate> _teammate;
  std::vector<std::vector<std::string> > _messages;

  size_t	_id;
  bool		_party;
  bool		_seek;
  size_t _lvl;
  size_t _inventory[7];
  size_t _goal[7];
  size_t _minEdge;
  size_t _nbCmd;
  size_t _partySize;
  int	 _x;
  int	 _y;
  int _socket;
  fd_set _set;
  int _nbClient;
  int _width;
  int _height;
  size_t _time;
  e_step _step;
  e_command _lastCommand;
  e_direction _direction;
  bool _lvlUp;
  bool _invite;
  bool _accept;
  bool _leader;
  bool _regroup;
  bool _reading;
  bool _here;
  std::string _leaderId;
  std::vector<std::string> _regroupMessage;

public: // Client.cpp
  Client(std::string const &, std::string const &, int);
  ~Client();

  void		createClient();
  bool		startLoop();
  bool		getAns();
  bool		handleClient();
  bool		handleServer();
  void		writeToSocket(std::string const &);
  void		checkCmd(std::string const &);
  e_step	sendTeamName(std::string const &);
  e_step	getNbClientAndCoords(std::string const &);
  bool		checkAns();
  void		checkLvlUp();

public: // AI.cpp
  void		startAI();
  void		defineTime();
  void		refreshTime();
  bool		parseInventory();
  bool	        checkInventory();
  void		forkUntil(size_t);
  void		initAI();
  void		initItems();
  void		checkTime();
  void		checkNbCommand();
  void		checkAlive();

public: // GetToNextLvl.cpp
  void		getToNextLvl();
  void	        seekNextLvl(size_t);
  void	        leaderTask(size_t, size_t, size_t, size_t, size_t, size_t);
  void		getToLvl2();
  void		getToLvl3();
  void		getToLvl4();
  void		getToLvl5();
  void		getToLvl6();
  void		getToLvl7();
  void		getToLvl8();
  void		seekParty();
  void		newLeader();

public: // Goal.cpp
  void		defineGoal(size_t, size_t, size_t, size_t,
			   size_t, size_t, size_t);
  void		searchGoal();
  bool		checkView();
  void		checkCoordItems(size_t);
  bool		checkGoal();
  void		cleanSquare();

public: // Food.cpp
  void		searchFood(size_t);
  void		checkViewFood();
  void		checkCoordFood(size_t);

public: //Command.cpp
  void		take(e_item);
  void	        put(e_item);
  void		goTake(int, int, size_t);
  void		look();
  void		parseLook();
  void		goForward();
  void		turnLeft();
  void		turnRight();
  void	        go(int, int);
  void		turn(e_direction);
  void		incantation();

public: //Message.cpp
  void		checkBroadcast();
  void		handleMultipleAns(std::vector<std::string> &);
  void	        readMessage(std::vector<std::string> const &);
  bool		checkTeamId(std::vector<std::string> const &);
  void		checkIncante();
  void		checkKick(std::string const &);
  void	        goToLeader(std::vector<std::string> const &);
  void	        checkId(std::vector<std::string> const &);
  void	        newMember(std::vector<std::string> const &, size_t);
  void	        checkSeekLvl(std::vector<std::string> const &);
  void	        checkInvite(std::vector<std::string> const &);
  void	        checkAccept(std::vector<std::string> const &);
  void	        sendAccept(std::vector<std::string> const &);
  void	        sendTeamUp(std::vector<std::string> const &); 
  void	        sendInvite(std::vector<std::string> const &);
  void	        sendDecline(std::vector<std::string> const &);
  void	        sendKick(std::string const &);
  void	        addTeamId(std::string const &);

};

#endif // CLIENT_HPP
