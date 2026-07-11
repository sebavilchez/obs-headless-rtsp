#include "OBSManager.h"
#include <iostream>

OBSManager::OBSManager() {}

OBSManager::~OBSManager() {
    shutdown();
}

bool OBSManager::initialize() {
    // Configuramos el directorio para que libobs encuentre sus dependencias
    SetDllDirectory(binPath.c_str());

    hObs = LoadLibrary(dllPath.c_str());
    if (!hObs) {
        std::cerr << "Error: No se pudo cargar obs.dll en: " << dllPath << std::endl;
        return false;
    }

    auto obs_startup = (obs_startup_t)GetProcAddress(hObs, "obs_startup");
    if (!obs_startup) {
        std::cerr << "Error: No se encontro la funcion obs_startup." << std::endl;
        return false;
    }

    if (!obs_startup("en-US", nullptr, nullptr)) {
        std::cerr << "Error: obs_startup fallo al iniciar el motor." << std::endl;
        return false;
    }

    std::cout << "¡EXITO! Motor libobs inicializado correctamente." << std::endl;
    return true;
}

void OBSManager::shutdown() {
    if (hObs) {
        auto obs_shutdown = (obs_shutdown_t)GetProcAddress(hObs, "obs_shutdown");
        if (obs_shutdown) {
            obs_shutdown();
            std::cout << "Motor libobs apagado correctamente." << std::endl;
        }
        FreeLibrary(hObs);
        hObs = nullptr;
    }
}