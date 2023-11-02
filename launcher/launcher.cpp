#include <iostream>
#include <string>
#include <future>
#include <cstdlib>

void run()
{
  system("sh r.sh");
}

int main()
{
  std::cout << "--------------------" << std::endl;
  std::cout << "|                  |" << std::endl;
  std::cout << "|  Merrli Console  |" << std::endl;
  std::cout << "|    Main v1.1     |" << std::endl;
  std::cout << "|                  |" << std::endl;
  std::cout << "--------------------" << std::endl;

  auto future = std::async(std::launch::async, run);

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
      return 0;
    } 
    else if(command == "run")
    {
      std::cout << "Running here: http://localhost:8001" << std::endl;   
    }
    else 
    {
      std::cout << "Unknow Command..." << std::endl;
    }
  }
}
