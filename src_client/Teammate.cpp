#include "Teammate.hpp"

Teammate::Teammate(std::string const &id, size_t time) :
  _id(id), _time(time)
{
}

Teammate::~Teammate()
{
}

std::string const &Teammate::getId() const
{
  return _id;
}

size_t	Teammate::getTime() const
{
  return _time;
}

void	Teammate::setTime(size_t time)
{
  _time = time;
}

bool	Teammate::checkTime(size_t time)
{
  if (_time >= time + 10000)
    return false;
  return true;
}
