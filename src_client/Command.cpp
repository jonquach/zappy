#include "Client.hpp"

void    Client::take(e_item type)
{
  _lastCommand = BASIC;
  writeToSocket("prend " + _items[type]);
  if (_ans == "ok")
    {
      _inventory[type]++;
      if (type == FOOD)
        {
          _time += 126;
          for (size_t i = 0; i < _teammate.size(); ++i)
            _teammate[i].setTime(_teammate[i].getTime() + 126);
        }
    }
}

void    Client::put(e_item type)
{
  _lastCommand = BASIC;
  writeToSocket("pose " + _items[type]);
  if (_ans == "ok")
    {
      _inventory[type]--;
      if (type == FOOD)
        _time -= 126;
    }
}

void    Client::look()
{
  _lastCommand = LOOK;
  writeToSocket("voir\n");
  parseLook();
}

void    Client::parseLook()
{
  std::stringstream     ss(_ans);
  std::string           tmp;
  size_t                i = 0;
  _view.clear();

  while(std::getline(ss, tmp, ','))
    {
      Coord c(tmp, i);
      _view.push_back(c);
      ++i;
    }

  std::cout << "THIS IS I : " << i << std::endl;

  size_t        max = 1;
  size_t        lvl = 0;
  size_t        coef = 1;

  while (max <= i - 1)
    {
      coef += 2;
      max += coef;
      ++lvl;
    }
  std::cout << "THIS IS LVL : " << lvl << std::endl;
  if (lvl != 0)
    _lvl = lvl;
}

void    Client::goForward()
{
  _lastCommand = BASIC;
  writeToSocket("avance\n");
  if (_direction == EAST)
    ++_x;
  else if (_direction == WEST)
    --_x;
  else if (_direction == SOUTH)
    ++_y;
  else if (_direction == NORTH)
    --_y;
}

void    Client::turnLeft()
{
  _lastCommand = BASIC;
  writeToSocket("gauche\n");
}

void    Client::turnRight()
{
  _lastCommand = BASIC;
  writeToSocket("droite\n");
}

void    Client::go(int x, int y)
{
  while (_x != x || _y != y)
    {
      if (_here == false && _regroup == false)
        {
          if (_x < x)
            turn(EAST);
          else if (_x > x)
            turn(WEST);
          else if (_y > y)
            turn(NORTH);
          else if (_y < y)
            turn(SOUTH);
          goForward();
        }
      else
        break;
    }
}

void    Client::goTake(int x, int y, size_t j)
{
  e_item        tmp = static_cast<e_item>(j);
  std::cout << "GOTO: " << x << "/" << y << std::endl;
  go(x, y);
  take(tmp);
}

void    Client::turn(e_direction dir)
{
  int   tmp = _direction - dir;

  if (tmp == -3)
    turnLeft();
  else if (tmp == 3)
    turnRight();
  else
    {
      while (tmp > 0)
        {
          turnLeft();
          --tmp;
        }
      while (tmp < 0)
        {
          turnRight();
          ++tmp;
        }
    }
  _direction = dir;
}

void    Client::incantation()
{
  _lvlUp = false;
  _lastCommand = INCANTATION;
  writeToSocket("incantation\n");
  std::cout << "incante : " << _ans << std::endl;
  if (_ans == "ko")
    {
      _here = false;
      _regroup = false;
    }
}
