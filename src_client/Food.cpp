#include "Client.hpp"

void    Client::searchFood(size_t time)
{
  size_t        tmp = 0;
  size_t        tmpTime = _time;
  size_t        threeSixty = 0;

  while (_time < time)
    {
      if (_here == false && _regroup == false)
        {
          look();
          checkViewFood();
          if (_time < time)
            {
              if (tmpTime + 1000 < _time)
                {
                  forkUntil(_time - 400);
                  tmpTime = _time;
                }
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

void    Client::checkViewFood()
{
  _x = 0;
  _y = 0;
  _direction = EAST;
  for (size_t i = 0; i < _view.size(); ++i)
    {
      if (_here == false && _regroup == false)
        checkCoordFood(i);
      else
        break;
      if (i > 8)
        break;
    }
}

void    Client::checkCoordFood(size_t i)
{
  size_t        j = _view[i].getItems(1);
  std::cout << "NUMBER OF FOOD: " << j << std::endl;
  while (j > 0)
    {
      if (_here == false && _regroup == false)
        goTake(_view[i].getX(), _view[i].getY(), 0);
      --j;
    }
}
