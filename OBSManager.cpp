#include "OBSManager.h"
#include <iostream>


OBSManager::OBSManager()
{
}


OBSManager::~OBSManager()
{
    shutdown();
}


bool OBSManager::initialize()
{
    SetDllDirectoryA(binPath.c_str());


    hObs = LoadLibraryA(dllPath.c_str());

    if (!hObs)
    {
        std::cerr 
            << "Error cargando obs.dll: "
            << dllPath
            << std::endl;

        return false;
    }


    auto obs_startup =
        (obs_startup_t)GetProcAddress(
            hObs,
            "obs_startup"
        );


    obs_shutdown =
        (obs_shutdown_t)GetProcAddress(
            hObs,
            "obs_shutdown"
        );


    obs_load_all_modules =
        (obs_load_all_modules_t)GetProcAddress(
            hObs,
            "obs_load_all_modules"
        );


    obs_post_load_modules =
        (obs_post_load_modules_t)GetProcAddress(
            hObs,
            "obs_post_load_modules"
        );


    if (!obs_startup)
    {
        std::cerr 
            << "No existe obs_startup"
            << std::endl;

        return false;
    }


    if (!obs_startup(
        "en-US",
        nullptr,
        nullptr))
    {
        std::cerr
            << "obs_startup fallo"
            << std::endl;

        return false;
    }


    std::cout
        << "libobs iniciado"
        << std::endl;



    if (!obs_load_all_modules)
    {
        std::cerr
            << "No existe obs_load_all_modules"
            << std::endl;

        return false;
    }


    if (!obs_post_load_modules)
    {
        std::cerr
            << "No existe obs_post_load_modules"
            << std::endl;

        return false;
    }



    obs_load_all_modules();


    std::cout
        << "Modulos cargados"
        << std::endl;



    obs_post_load_modules();


    std::cout
        << "Modulos inicializados"
        << std::endl;


    return true;
}



void OBSManager::shutdown()
{
    if (hObs)
    {

        if (obs_shutdown)
        {
            obs_shutdown();

            std::cout
                << "libobs cerrado"
                << std::endl;
        }


        FreeLibrary(hObs);

        hObs = nullptr;
    }
}

void OBSManager::listSources()
{
    std::cout << "Listado de fuentes registradas:" << std::endl;

    // Esta etapa solamente prueba que los módulos cargaron.
    // La enumeración real la hacemos en el siguiente paso.
    
    std::cout << "OK: Modulos OBS activos" << std::endl;
}
