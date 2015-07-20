#ifndef TEAMMATE_HPP
#define TEAMMATE_HPP

#include <iostream>
#include <vector>
#include <sstream>
#include <string>

class Teammate
{
private:
  std::string	_id;
  size_t	_time;

public:
  Teammate(std::string const &, size_t);
  ~Teammate();
  std::string const &getId() const;
  size_t getTime() const;
  void setTime(size_t);
  bool checkTime(size_t);
};

#endif //TEAMMATE_HPP
