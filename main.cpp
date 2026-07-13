#include "OBSManager.h"
#include <iostream>


int main()
{
    OBSManager obs;


    if (!obs.initialize())
    {
        return 1;
    }


    obs.listSources();


    std::cout
        << "ENTER para salir..."
        << std::endl;


    std::cin.get();


    return 0;
}
