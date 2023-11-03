#include "launcher.hpp"

void server_debug(std::string port)
{
    std::string command = "curl -I http://localhost:" + port;
    system(command.c_str());
}
