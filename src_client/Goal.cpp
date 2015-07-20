#include "Client.hpp"

void    Client::defineGoal(size_t f, size_t l, size_t d, size_t s, size_t m,
			   size_t p, size_t t)
{
  _goal[0] = f;
  _goal[1] = l;
  _goal[2] = d;
  _goal[3] = s;
  _goal[4] = m;
  _goal[5] = p;
  _goal[6] = t;
}

void    Client::searchGoal()
{
  size_t        tmp = 0;
  size_t        threeSixty = 0;
  bool  ready = false;

  while (ready != true)
    {
      if (_here == false && _regroup == false)
        {
	  std::cout << "FOOD : " << _inventory[0] << std::endl;
          look();
          ready = checkView();
          if (ready != true)
            {
              if (_x != 0 || _y != 0)
                tmp = 0;
              if (tmp < _minEdge)
                {
                  goForward();
                  ++tmp;
                }
              else
                {
                  turnLeft();
                  ++threeSixty;
                  if (threeSixty == 4)
                    {
                      goForward();
                      threeSixty = 0;
                    }
                  tmp = 0;
                }
            }
        }
      else
        break;
    }
}

bool    Client::checkView()
{
  _x = 0;
  _y = 0;
  _direction = EAST;
  for (size_t i = 0; i < _view.size(); ++i)
    {
      checkCoordItems(i);
      if (checkGoal() == true)
        return true;
      if (i > 30)
        break;
    }
  return false;
}

void    Client::checkCoordItems(size_t i)
{
  size_t        j = 0;

  while (j < 7)
    {
      if (_inventory[j] < _goal[j])
        if (_view[i].getItems(j + 1) > 0 && _view[i].getItems(0) == 0)
          goTake(_view[i].getX(), _view[i].getY(), j);
      ++j;
    }
}

bool    Client::checkGoal()
{
  size_t        check = 0;

  for (int i = 0; i < 7; ++i)
    {
      if (_inventory[i] >= _goal[i])
        ++check;
    }
  if (check == 7)
    return true;
  return false;
}

void    Client::cleanSquare()
{
  std::cout << "CLEAN SQUARE" << std::endl;

  size_t        j = 1;
  size_t        tmp;

  std::cout << "PUT AND TAKE" << std::endl;
  while (j < 7)
    {
      tmp = _view[0].getItems(j + 1);
      std::cout << "TULULU" << std::endl;
      if (tmp > _goal[j])
        while (tmp > _goal[j])
          {
	    std::cout << "TAKE" << std::endl;
	    std::cout << "TO TAKE: " << tmp << std::endl;
	    std::cout << "TO HAVE: " << _goal[j] << std::endl;
            take(static_cast<e_item>(j));
            if (_ans == "ok")
              tmp--;
            else
              {
                look();
                tmp = _view[0].getItems(j + 1);
              }
          }
      else if (tmp < _goal[j])
        while (tmp < _goal[j] && _inventory[j] > 0)
          {
	    std::cout << "PUT" << std::endl;
	    std::cout << "TO PUT: " << tmp << std::endl;
	    std::cout << "TO HAVE: " << _goal[j] << std::endl;
            put(static_cast<e_item>(j));
            if (_ans == "ok")
              tmp++;
            else
              {
                look();
                tmp = _view[0].getItems(j + 1);
              }
          }
      ++j;
    }
  std::cout << "END PUT AND TAKE" << std::endl;
}
