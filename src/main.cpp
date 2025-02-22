#include <iostream>
#include "files.h"
#include "Models/GarbageCollector.h"
#include "Menu.h"


int main() {
    {
        Menu menu = Menu();
        menu.start();

        while (true)
        {
            try
            {
                std::string command = menu.getCommand();
                menu.executeCommand(command);
            }
            catch (std::exception& e)
            {
                std::cerr << e.what() << std::endl;
            }
        }
    }
}