#include "Exception.hpp"
#include "ParseArg.hpp"
#include "Client.hpp"

static int usage(char const *av) {
    std::cerr << "[Usage] : " << av
              << " -n [TEAM NAME] -p [PORT] -h"
              << " [IP][DEFAULT : 127.0.0.1]"
              << std::endl;
    return -1;
}

int main(int ac, char const **av) {
    try {
        if (ac > 7)
            return usage(av[0]);

        ParseArg parse(ac, av);

        if (parse.checkNb() == false
            || parse.checkArg() == false
            || parse.findArg() == false)
            return usage(av[0]);

        Client client(parse.getIp(), parse.getTeamName(), parse.getPort());

        client.createClient();
        client.startLoop();
    }
    catch (std::exception &e) {
        std::cerr << "\033[1;31m" << e.what() << "\033[0m" << std::endl;
    }
    return 0;
}
