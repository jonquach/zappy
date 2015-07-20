#include "Client.hpp"

void    Client::checkBroadcast()
{
  std::vector<std::string>      v;
  std::string                   tmp = _ans;

  if (_ans.find("\n") < _ans.size())
    handleMultipleAns(v);
  else
    {
      if (tmp.find(",") < tmp.size())
        tmp.replace(tmp.find(","), 1, " ");
      std::istringstream iss(tmp);

      while (iss)
        {
	  std::string str;

          iss >> str;
          if (!str.empty())
            v.push_back(str);
        }
      if (v.size() > 3 && v[0] == "message")
        {
          if (v[2] == _leaderId && v[3] == "regroup")
            {
              _regroupMessage.clear();
              _regroupMessage = v;
            }
          else if (v[3] != "regroup")
            {
	      std::cout << "PUSH" << std::endl;
              _messages.push_back(v);
            }
          getAns();
        }
    }
}

void    Client::handleMultipleAns(std::vector<std::string> &v)
{
  std::stringstream     ss(_ans);
  std::string           tmp;
  std::string           trueAns = _ans;

  while(std::getline(ss, tmp, '\n'))
    {
      if (tmp.find(",") < tmp.size())
        tmp.replace(tmp.find(","), 1, " ");
      v.clear();

      std::istringstream iss(tmp);

      while (iss)
        {
	  std::string str;

          iss >> str;
          if (!str.empty())
            v.push_back(str);
        }
      if (v.size() > 3 && v[0] == "message")
        {
          if (v[2] == _leaderId && v[3] == "regroup")
            {
              _regroupMessage.clear();
              _regroupMessage = v;
            }
          else if (v[3] != "regroup")
            _messages.push_back(v);
        }
      else
        if (trueAns.find("niveau") >= _ans.size())
          trueAns = tmp;
    }
  _ans = trueAns;
}

void    Client::readMessage(std::vector<std::string> const &v)
{
  std::cout << "READMESSAGE" << std::endl;
  std::vector<std::string> tmp = v;

  if (_time > 1000 && checkTeamId(tmp) == false)
    {
      tmp = v;
      if (_seek == true)
        {
          tmp = v;
          if (_accept == false && v.size() > 3)
            {
              if (v[3] == "seek" && _invite == false && _accept == false)
                checkSeekLvl(tmp);
              else if (v[3] == "invite")
                checkId(tmp);
              else if (v[3] == "accept")
                checkId(tmp);
            }
          if (_party == false || _teammate.size() < _partySize)
            {
              if (tmp[3] == "teamup" || tmp[3] == "decline")
                checkId(tmp);
            }
        }
    }
}

bool    Client::checkTeamId(std::vector<std::string> const &v)
{
  std::cout << "CHECKTEAMID" << std::endl;

  if (_party == true && v.size() > 3)
    for (size_t i = 0; i < _teammate.size(); ++i)
      {
        if (v[2] == _teammate[i].getId())
          {
            if (v[3] == "alive")
              _teammate[i].setTime(_time);
            else if (v[3] == "regroup" && v[2] == _leaderId &&
                     _leader == false)
              goToLeader(v);
            else if (v[3] == "here" && _leader == true)
	      checkIncante();
            else if (v[3] == "kick" && v[2] == _leaderId && _leader == false)
	      checkKick(v[4]);
	    return true;
	  }
      }
  return false;
}

void	Client::checkIncante()
{
  static size_t here = 0;

  ++here;
  std::cout << "HERE:" << here << std::endl;
  if (here == _partySize)
    {
      std::cout << "GONNA INCANTE:" << here << std::endl;
      here = 0;
      cleanSquare();
      incantation();
    }
}

void	Client::checkKick(std::string const &id)
{
  size_t myId;
  std::stringstream s;

  s << id;
  s >> myId;
  if (myId == _id)
    {
      _here = false;
      _regroup = false;
      _leader = true;
      _invite = false;
      _seek = true;
      _accept = false;
      _party = false;
      _teammate.clear();
    }
}

void    Client::goToLeader(std::vector<std::string> const &v)
{
  size_t        direction;
  std::stringstream str;

  str << v[1];
  str >> direction;
  if (direction != 0)
    _here = false;
  if (direction == 1 || direction == 2 || direction == 8)
    goForward();
  else if (direction == 3 || direction == 4)
    turnLeft();
  else if (direction == 5)
    {
      turnLeft();
      turnLeft();
    }
  else if (direction == 6 || direction == 7)
    turnRight();
  if (direction == 0 && _time > 3000 && _here == false)
    {
      _here = true;
      std::stringstream msg;
      msg << "broadcast " << _id << " here\n";
      _lastCommand = BASIC;
      writeToSocket(msg.str());
    }
  else if (_time < 3000)
    searchFood(6000);
  _regroup = true;
}

void    Client::checkId(std::vector<std::string> const &v)
{
  size_t        id;

  if (v.size() > 5)
    {
      std::stringstream str;

      str << v[4];
      str >> id;
      if (_id == id)
        {
          if ((v[3] == "accept" || v[3] == "teamup")
              && _teammate.size() < _partySize && _leader == true)
	    newMember(v, id);
          else if (v[3] == "accept")
            sendDecline(v);
          else if (v[3] == "decline")
            {
              _accept = false;
              _invite = false;
            }
          else if (v[3] == "invite")
            {
              if (_invite == false)
                sendAccept(v);
              else
                sendDecline(v);
            }
        }
    }
}

void	Client::newMember(std::vector<std::string> const &v, size_t id)
{
  std::stringstream str;

  if (v[3] == "accept")
    sendTeamUp(v);
  str << v[2];
  str >> id;
  if (_id < id)
    {
      if (_teammate.size() > 0)
	newLeader();
      _leader = false;
      _leaderId = v[2];
    }
  else
    _leader = true;
  _accept = false;
  _invite = false;
  _seek = false;
  _party = true;
  addTeamId(v[2]);
}

void    Client::addTeamId(std::string const &name)
{
  bool  exist = false;
  for (size_t i = 0; i < _teammate.size(); ++i)
    {
      if (name == _teammate[i].getId())
        exist = true;
    }
  if (exist == false)
    {
      Teammate  tmp(name, _time);

      _teammate.push_back(tmp);
      _invite = false;
      _accept = false;
      _seek = true;
    }
  std::cout << "PARTY SIZE:" << _teammate.size() << std::endl;
}

void    Client::checkSeekLvl(std::vector<std::string> const &v)
{
  size_t        lvl;

  if (_teammate.size() < _partySize && v.size() > 4)
    {
      std::stringstream str;

      str << v[4];
      str >> lvl;
      if (_lvl == lvl)
        sendInvite(v);
    }
}

void    Client::sendInvite(std::vector<std::string> const &v)
{
  std::stringstream str;

  str << "broadcast " << _id << " invite " << v[2] << " " << _lvl << "\n";
  _lastCommand = BASIC;
  writeToSocket(str.str());
  _invite = true;
}

void    Client::sendKick(std::string const &name)
{
  std::stringstream str;

  str << "broadcast " << _id << " kick " << name << "\n";
  _lastCommand = BASIC;
  writeToSocket(str.str());
  _invite = true;
}

void    Client::sendTeamUp(std::vector<std::string> const &v)
{
  std::stringstream str;

  str << "broadcast " << _id << " teamup " << v[2] << " " << _lvl << "\n";
  _lastCommand = BASIC;
  writeToSocket(str.str());

}

void    Client::sendAccept(std::vector<std::string> const &v)
{
  std::stringstream str;

  str << "broadcast " << _id << " accept " << v[2] << " " << _lvl << "\n";
  _lastCommand = BASIC;
  writeToSocket(str.str());
  _invite = false;
  _accept = true;
}

void    Client::sendDecline(std::vector<std::string> const &v)
{
  std::stringstream str;

  str << "broadcast " << _id << " decline " << v[2] << " " << _lvl << "\n";
  _lastCommand = BASIC;
  writeToSocket(str.str());
}

void    Client::newLeader()
{
  std::stringstream str;

  for (size_t i = 0; i < _teammate.size(); ++i)
    {
      str << "broadcast " << _id << " kick " << _teammate[i].getId() << "\n";
      _lastCommand = BASIC;
      writeToSocket(str.str());
      str.clear();
    }
  _teammate.clear();
}
