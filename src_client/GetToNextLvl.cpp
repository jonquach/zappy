#include "Client.hpp"

void	Client::getToNextLvl()
{
  if (_lvl == 1)
    getToLvl2();
  if (_lvl == 2)
    getToLvl3();
  if (_lvl == 3)
    getToLvl4();
  if (_lvl == 4)
    getToLvl5();
  if (_lvl == 5)
    getToLvl6();
  if (_lvl == 6)
    getToLvl7();
  if (_lvl == 7)
    getToLvl8();
}

void	Client::getToLvl2()
{
  checkTime();
  defineGoal(60, 1, 0, 0, 0, 0, 0);
  searchGoal();
  cleanSquare();
  incantation();
  if (_lvl == 2)
    getToLvl3();
  getToLvl2();
}

void	Client::seekNextLvl(size_t lvl)
{
  if (_lvl == lvl)
    {
      _regroup = false;
      _here = false;
      getToNextLvl();
    }
  checkTime();
  if (_time < 1000)
    {
      _here = false;
      _regroup = false;
    }
  if (_here == false)
    {
      seekParty();
      if (_leader == false && _regroup == false)
      	{
      	  defineGoal(60, 0, 0, 0, 0, 0, 0);
      	  searchGoal();
      	}
      else
	{
	  look();
	  defineGoal(0, 0, 0, 0, 0, 0, 0);
	}
    }
  else
    look();
}

void	Client::leaderTask(size_t l, size_t d, size_t s,
			   size_t m, size_t p, size_t t)
{
  if (_leader == true)
    {
      static size_t lvl = _lvl;
      static bool regroup = false;

      if (lvl < _lvl)
	{
	  _regroup = false;
	  lvl = _lvl;
	}
      if (_time < 2000)
	regroup = false;
      if (regroup == false)
	defineGoal(60, l, d, s, m, p, t);
      else
	defineGoal(0, l, d, s, m, p, t);
      searchGoal();
      regroup = true;
      std::stringstream str;

      str << "broadcast " << _id << " regroup\n";
      _lastCommand = BASIC;
      writeToSocket(str.str());
    }
}

void	Client::getToLvl3()
{
  seekNextLvl(3);
  leaderTask(1, 1, 1, 0, 0, 0);
  getToLvl3();
}

void	Client::getToLvl4()
{
  seekNextLvl(4);
  leaderTask(2, 0, 1, 0, 2, 0);
  getToLvl4();
}

void	Client::getToLvl5()
{
  seekNextLvl(5);
  leaderTask(1, 1, 2, 0, 1, 0);
  getToLvl5();
}

void	Client::getToLvl6()
{
  seekNextLvl(6);
  leaderTask(1, 2, 1, 3, 0, 0);
  getToLvl6();
}

void	Client::getToLvl7()
{
  seekNextLvl(7);
  leaderTask(1, 2, 3, 0, 1, 0);
  getToLvl7();
}

void	Client::getToLvl8()
{
  seekNextLvl(8);
  leaderTask(2, 2, 2, 2, 2, 1);
  getToLvl8();
}

void	Client::seekParty()
{
  _seek = true;
  std::stringstream str;

  if (_lvl < 4)
    _partySize = 1;
  else if (_lvl < 6)
    _partySize = 3;
  else if (_lvl < 8)
    _partySize = 5;
  else
    _partySize = 0;

  str << "broadcast " << _id << " seek " << _lvl << "\n";
  while (_party != true || (_teammate.size() < _partySize && _leader == true))
    {
      checkTime();
      
      _lastCommand = BASIC;
      writeToSocket(str.str());
      
      if (_party != true || (_teammate.size() < _partySize && _leader == true))
      	{
      	  forkUntil(_time - 100);
      	  searchFood(_time + 100);
      	}
      _accept = false;
      _invite = false;
    }
}
