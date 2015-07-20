#include "Coord.hpp"

Coord::Coord(std::string const &str, size_t const &i) :
  _x(0), _y(0)
{
  initItems();
  initNames();
  setCoord(i);
  parseItems(str);
}

Coord::~Coord()
{}

void	Coord::initItems()
{
  for (size_t i = 0; i < 8; ++i)
    _items[i] = 0;
}

void    Coord::initNames()
{
  std::string   str;

  str = "joueur";
  _names.push_back(str);
  str = "nourriture";
  _names.push_back(str);
  str = "linemate";
  _names.push_back(str);
  str = "deraumere";
  _names.push_back(str);
  str = "sibur";
  _names.push_back(str);
  str = "mendiane";
  _names.push_back(str);
  str = "phiras";
  _names.push_back(str);
  str = "thystame";
  _names.push_back(str);
}

void	Coord::setCoord(size_t const &i)
{
  size_t	coefMid = 0;
  size_t	coefMax = 1;
  size_t	mid = 0;
  size_t	max = 1;

  while (max <= i)
    {
      coefMid += 2;
      coefMax += 2;
      mid += coefMid;
      max += coefMax;
      ++_x;
    }
  _y = i - mid;
}

void	Coord::parseItems(std::string const &str)
{
  std::string	tmp(str);
  for (size_t i = 0; i < _names.size(); ++i)
    {
      // std::cout << "OLD : " << tmp << std::endl;
      while (tmp.find(_names[i]) < tmp.size())
	{
	  tmp.replace(tmp.find(_names[i]), _names[i].size(), "");
	  _items[i]++;
	}
      // std::cout << "NEW : " << tmp << std::endl;
      // std::cout << "ITEM " << i << ": " << _items[i] << std::endl;
    }
}

int	Coord::getX() const
{
  return this->_x;
}

int    Coord::getY() const
{
  return this->_y;
}

size_t	Coord::getItems(size_t i) const
{
  if (i < 8)
    return this->_items[i];
  return (0);
}
