#include "Exception.hpp"

NException::NException(std::string const &msg) :
  _msg(msg)
{

}

const char *NException::what() const throw()
{
  return _msg.c_str();
}
