#include "OBSManager.h"
#include <iostream>

int main() {
    OBSManager obs;

    // Fase 1: Iniciar el motor
    if (!obs.initialize()) {
        return 1;
    }

    // El motor estara encendido hasta que el objeto 'obs' salga de contexto o se cierre el programa
    std::cout << "Presiona Enter para cerrar el backend..." << std::endl;
    std::cin.get();

    return 0;
}