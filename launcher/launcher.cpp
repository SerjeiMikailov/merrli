#include "launcher.hpp"

void run()
{
  system("cd .. && cd launcher && sh r.sh");
}

int main()
{
  std::cout << "---------------------" << std::endl;
  std::cout << "|                   |" << std::endl;
  std::cout << "|  Merrli Terminal  |" << std::endl;
  std::cout << "|     Main v1.1     |" << std::endl;
  std::cout << "|                   |" << std::endl;
  std::cout << "---------------------" << std::endl;

  auto future = std::async(std::launch::async, run);

  std::string port;

  std::cout << " " << std::endl;
  std::cout << "Send the port that your server is running:" << std::endl;
  std::cout << "-> ";
  std::cin >> port;
 
  if(port != "*&^*")
  {
    std::cout << " " << std::endl;
    std::cout << "Your port is: " << port << std::endl;
    std::cout << "If you need, just say 'help'..." << std::endl;
  }

  while(future.wait_for(std::chrono::seconds(0)) != std::future_status::ready)
  {
    std::string command; 

    std::cout << " " << std::endl;
    std::cout << "-> ";
    std::cin >> command;

    if(command == "version")
    {
      std::cout << "Main v1.1" << std::endl;
    } 
    else if(command == "exit")
    { 
      system("pkill l");
      return 0;
    } 
    else if(command == "run")
    {
      std::cout << "Running here: http://localhost:" << port << std::endl;   
    }
    else if(command == "help")
    {
      std::cout << "Avaible commands: " << std::endl;

      std::cout << "'version'" << std::endl;
      std::cout << "'exit'" << std::endl;
      std::cout << "'debug'" << std::endl;
      std::cout << "'run'" << std::endl;
    }
    else if(command == "debug")
    {
      server_debug(port);   
    }
    else 
    {
      std::cout << "Unknow Command..." << std::endl;
    }
  }
}
