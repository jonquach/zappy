#include <sys/types.h>
#include "Client.hpp"

void	Client::startAI()
{
  initAI();
  if (_inventory[0] <= 10)
    forkUntil(1000);
  defineGoal(40, 0, 0, 0, 0, 0, 0);
  searchFood(2500);
  look();
  getToNextLvl();
  sleep(1000);
}

void	Client::initAI()
{
  _time = 1260;
  _party = false;
  _seek = false;
  _accept = false;
  _invite = false;
  _leader = true;
  _leaderId = "";
  _lvl = 0;
  _messages.clear();
  _teammate.clear();
  srand(time(NULL));
  _id = rand() % 100000000 + ::getpid();
  _nbCmd = 0;
  if (_height < _width)
    _minEdge = _width;
  else
    _minEdge = _height;
  initItems();
  defineTime();
}

void	Client::initItems()
{
  std::string	str;

  str = "nourriture\n";
  _items.push_back(str);
  str = "linemate\n";
  _items.push_back(str);
  str = "deraumere\n";
  _items.push_back(str);
  str = "sibur\n";
  _items.push_back(str);
  str = "mendiane\n";
  _items.push_back(str);
  str = "phiras\n";
  _items.push_back(str);
  str = "thystame\n";
  _items.push_back(str);
  _inventory[0] = 10;
  for (size_t i = 1; i < 7; ++i)
    _inventory[0] = 0;
}

void	Client::defineTime()
{
  _lastCommand = INVENTORY;
  writeToSocket("inventaire\n");
  
  parseInventory();
  _time = (_inventory[0] - 1) * 126;
  refreshTime();
}

void    Client::refreshTime()
{
  if (_lastCommand == INCANTATION && _time >= 300)
    _time -= 300;
  else if (_lastCommand == FORK && _time >= 42)
    _time -= 42;
  else if (_time >= 7)
    _time -= 7;
  _inventory[0] = _time / 126;
}

bool	Client::checkInventory()
{
  std::string str;
  std::istringstream ss(_ans);

  ss >> str;
  if (str == "{nourriture")
    return true;
  return false;
}

bool    Client::parseInventory()
{
  std::vector<std::string> v;

  while (_ans.find(",") < _ans.size())
    _ans.replace(_ans.find(","), 1, " ");
  if (_ans.find("}") < _ans.size())
    _ans.replace(_ans.find("}"), 1, " ");
  std::istringstream ss(_ans);

  while (ss)
    {
      std::string str;

      ss >> str;
      if (!str.empty())
	v.push_back(str);
    }
  if (v.size() == 14)
    {
      std::stringstream sstream;
      size_t i = 1;
      size_t j = 0;

      while (i < 14 && j < 7)
	{
	  sstream << v[i];
	  sstream >> _inventory[j];
	  sstream.clear();
	  i += 2;
	  ++j;
	}
      return true;
    }
  return false;
}

void	Client::forkUntil(size_t time)
{
  std::stringstream str;

  while (_time > time)
    {
      _lastCommand = FORK;
      writeToSocket("fork\n");
      
    }
  defineTime();
}

void	Client::checkTime()
{
  checkNbCommand();
  checkAlive();
  if (_time < 1000)
    {
      _here = false;
      _regroup = false;
      searchFood(5000);
    }
}

void	Client::checkNbCommand()
{
  if (_nbCmd >= 20)
    {
      if (_party == true)
	{
	  std::stringstream str;

	  str << "broadcast " << _id << " alive\n";
	  _lastCommand = BASIC;
	  writeToSocket(str.str());
	}
      defineTime();
      _nbCmd = 0;
    }
}

void	Client::checkAlive()
{
  if (_party == true)
    for (size_t i = 0; i < _teammate.size(); ++i)
      {
	if (_teammate[i].checkTime(_time) == false)
	  {
	    if (_leader == true)
	      sendKick(_teammate[i].getId());
	    if (_teammate[i].getId() == _leaderId)
	      {
		_leader = false;
		_leaderId = "";
	      }
	    _teammate.erase(_teammate.begin() + i);
	    if (_teammate.size() == 0)
	      {
		_accept = false;
		_invite = false;
		_seek = true;
		_party = false;
		_leader = true;
		seekParty();
	      }
	  }
      }
}
