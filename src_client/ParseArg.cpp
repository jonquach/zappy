#include "ParseArg.hpp"

ParseArg::ParseArg(int ac, char const **av)
    : _nb(ac), _ip("127.0.0.1"), _arg(av, av + ac)
{
    _name = _arg[0];
    if (!_arg.empty())
        _arg.erase(_arg.begin());
}

ParseArg::~ParseArg() {

}

bool ParseArg::findArg() {
    for (size_t i = 0; i < _arg.size(); ++i) {

        if (_arg[i] == "-n" && i + 1 <= _arg.size())
            _teamName = _arg[i + 1];
        if (_arg[i] == "-p" && i + 1 <= _arg.size()) {
            try {
                std::istringstream ss(_arg[i + 1]);
                ss >> _port;
                if (checkPortRange() == false)
                    return false;
            } catch (std::invalid_argument &e) {
                std::cerr << "Invalid argument : port is in number"
                          << std::endl; 
                return false;
            } catch (std::out_of_range &e) {
                std::cerr << "Invalid port range : valid port range"
                          << " are 1024 to 65535" << std::endl; 
                return false;
            }
        }
        if (_arg[i] == "-h" && i + 1 <= _arg.size())
            _ip = _arg[i + 1];

        // std::cout << *(it) << std::endl;
    }
    return true;
}

bool ParseArg::checkArg() const {
    if (std::find(_arg.begin(), _arg.end(), "-p") != _arg.end()
        && std::find(_arg.begin(), _arg.end(), "-n") != _arg.end())
        return true;
    return false;
}

bool ParseArg::checkNb() const {
    if (_arg.size() % 2 != 0 || _arg.size() < 4 || _arg.size() > 6)
        return false;
    return true;
}

bool ParseArg::checkPortRange() const {
    if (_port > 1023 && _port <= 65535)
        return true;
    return false;
}

int ParseArg::getPort() const {
    return _port;
}

std::string const &ParseArg::getIp() const {
    return _ip;
}

std::string const &ParseArg::getName() const {
    return _name;
}

std::string const &ParseArg::getTeamName() const {
    return _teamName;
}
