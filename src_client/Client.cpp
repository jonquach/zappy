#include "Client.hpp"

Client::Client(std::string const &ip, std::string const &teamName, int port)
  : _port(port), _ip(ip), _teamName(teamName), _step(WELCOME_STEP)
{
  std::cout << "\033[1;32m[CLIENT] : Initialization"
	    << ", wait me to be ready...\033[0m" << std::endl
	    << "\033[1;32m[CLIENT] : Port : " << _port << ", IP Address : "
	    << _ip << ", Team Name : " << _teamName << "\033[0m" << std::endl;
}

Client::~Client()
{
  std::cout << "\033[1;32m[CLIENT] : Bye bye !\033[0m" << std::endl;
}

void Client::createClient()
{
  struct protoent *proto;
  struct sockaddr_in sin;

  if ((proto = getprotobyname("TCP")) == 0)
    throw NException("Error : getprotobyname failed");
  if ((_socket = socket(AF_INET, SOCK_STREAM, proto->p_proto)) == -1)
    throw NException("Error : socket failed");

  sin.sin_family = AF_INET;
  sin.sin_port = htons(_port);

  if ((sin.sin_addr.s_addr = inet_addr(_ip.c_str())) == INADDR_NONE)
    throw NException("Error : inet_addr failed");
  if (connect(_socket, (const struct sockaddr *)&sin, sizeof(sin)) == -1)
    throw NException("Error : connect failed");
}

bool Client::startLoop()
{
  while (_step != GAME_STEP)
    if (getAns() == false)
      return false;
  startAI();
  return true;
}

bool Client::getAns()
{
  FD_ZERO(&_set);
  FD_SET(_socket, &_set);

  if (select(_socket + 1, &_set, NULL, NULL, NULL) == -1)
    throw NException("Error : select failed");
  if (FD_ISSET(_socket, &_set))
    if (handleServer() == false)
      return false;
  return true;
}

bool Client::handleServer()
{
  static char buff[32768];
  int len;

  std::memset(buff, '\0', 32768);

  if ((len = read(_socket, buff, 32767)) <= 0) {
  
    if (close(_socket) == -1)
      std::cerr << "Error : close failed" << std::endl;

    throw NException("Error : read failed");
  }

  std::string buffer(buff);

  if (!buffer.empty() && buffer[buffer.length() - 1] == '\n')
    buffer.erase(buffer.length() - 1);
  _ans = buffer;

  std::cout << "\033[1;31m[SERVER] : " << buffer << "\033[0m" << std::endl;

  if (_step == GAME_STEP) {
    if (buffer == "mort")
      {
	std::cout << "You died" << std::endl;
	return false;
      }

  } else {
    checkCmd(buff);
    if (_step == Client::ERROR_STEP)
      return false;
  }

  checkAns();
  
  return true;
}

bool	Client::checkAns()
{
  checkBroadcast();
  if (_ans.find("niveau") >= _ans.size())
    {
      if (_lastCommand == INVENTORY && checkInventory() == false)
	getAns();
      else if (_lastCommand == BASIC && _ans != "ok" && _ans != "ko")
	{
	  getAns();
	}
      else if (_lastCommand == INCANTATION && _ans != "ko")
	checkLvlUp();
      else if (_lastCommand == LOOK && _ans.at(_ans.length() - 1) != '}'
	       && _ans.at(0) != '{')
	return true;
    }
  else if (_lvlUp == false)
    {
      _lvlUp = true;
      ++_lvl;
    }
  return false;
}

void	Client::checkLvlUp()
{
  if (_ans.find("niveau") < _ans.size())
    _lvlUp = true;
  else if (_lvlUp == false)
    getAns();
}

void Client::writeToSocket(std::string const &buffer)
{
  int len = buffer.size();
  int len2;

  len2 = 0;
  if (_step == GAME_STEP)
    ++_nbCmd;
  std::string buff(buffer);

  if (!buff.empty() && buffer[buff.length() - 1] == '\n')
    buff.erase(buff.length() - 1);

  std::cout << "\033[1;34m[CLIENT] Sending message : " << buff << "\033[0m"
	    << std::endl;

  while (len2 < len)
    {
      if ((len2 += write(_socket, buffer.c_str() + len2, len)) == -1)
	throw NException("Error : write failed");
    }
  if (_step == GAME_STEP)
    {
      refreshTime();
      getAns();
      if (_messages.size() == 0 && _regroupMessage.size() > 3
	  && _reading == false)
	{
	  _reading = true;
	  readMessage(_regroupMessage);
	  _reading = false;
	  _regroupMessage.clear();
	}
      if (_messages.size() > 0 && _reading == false)
	{
	  std::cout << "READING" << std::endl;
	  _reading = true;
	  for (size_t i = 0; i < _messages.size() ; ++i)
	    readMessage(_messages[i]);
	  _messages.clear();
	  if (_regroupMessage.size() > 3)
	    readMessage(_regroupMessage);
	  _regroupMessage.clear();
	  std::cout << "CLEAR" << std::endl;
	  _reading = false;
	  std::cout << "STOP READING" << std::endl;
	  std::cout << "TIME: " << _time << std::endl;
	}
    }
}

void Client::checkCmd(std::string const &buffer)
{
  switch (_step) {
  case Client::WELCOME_STEP:
    _step = sendTeamName(buffer);
    break;
  case Client::DATA_STEP:
    _step = getNbClientAndCoords(buffer);
    break;
  default:
    _step = Client::GAME_STEP;
    break;
  }
}

enum Client::e_step Client::sendTeamName(std::string const &buffer)
{
  if (buffer == "BIENVENUE") {
    return Client::WELCOME_STEP;
  }

  writeToSocket(_teamName + "\n");
  return Client::DATA_STEP;
}

enum Client::e_step Client::getNbClientAndCoords(std::string const &buffer)
{
  std::vector<std::string> v;
  std::stringstream ss;

  ss << buffer;

  while (ss) {
    std::string str;

    ss >> str;
    if (!str.empty())
      v.push_back(str);
  }

  if (v.size() == 4 && buffer == "mort")
    return Client::ERROR_STEP;

  if (v.size() == 1) {
    std::stringstream sstream;
    sstream << v[0];
    sstream >> _nbClient;
    return Client::DATA_STEP;
  }
  if (v.size() == 2) {
    std::stringstream sstream;

    sstream << v[0];
    sstream >> _width;
    sstream.clear();
    sstream << v[1];
    sstream >> _height;

    std::cout << "\033[1;32m[CLIENT] : " << "My client ID is " << _nbClient
	      << " on this server. The map is " << _width
	      << " width and " << _height << " height\033[0m" << std::endl;

    std::cout << "\033[1;32m[Client] : Ready !\033[0m" << std::endl;
  }

  return Client::GAME_STEP;
}
