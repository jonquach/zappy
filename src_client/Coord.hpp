#ifndef		COORD_HPP_
#define		COORD_HPP_

#include <iostream>
#include <vector>
#include <sstream>
#include <string>

class		Coord
{
private:
  int _x;
  int _y;
  size_t _items[8];
  std::vector<std::string> _names;

public:
  Coord(std::string const &, size_t const &);
  ~Coord();

public:
  void		setCoord(size_t const &);
  void		parseItems(std::string const &);
  void		initItems();
  void		initNames();
  int		getX() const;
  int		getY() const;
  size_t	getItems(size_t) const;
};

#endif
