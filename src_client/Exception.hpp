#ifndef EXCEPTION_HPP_
#define EXCEPTION_HPP_

#include <exception>
#include <string>

class NException : public std::exception
{
private:
  std::string _msg;

public:
  NException(std::string const &);
  virtual ~NException() throw() {}
  virtual const char *what() const throw();
};

#endif
