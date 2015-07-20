#ifndef PARSEARG_HPP_
#define PARSEARG_HPP_

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include "Exception.hpp"

class ParseArg
{
private:
    int _nb;
    int _port;
    std::string _ip;
    std::string _name;
    std::string _teamName;
    std::vector<std::string> _arg;

public:
    ParseArg(int, char const **);
    ~ParseArg();

    bool findArg();
    bool checkArg() const;
    bool checkNb() const;
    bool checkPortRange() const;
    int getPort() const;
    std::string const &getIp() const;
    std::string const &getName() const;
    std::string const &getTeamName() const;
};

#endif 
