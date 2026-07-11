#ifndef OBS_MANAGER_H
#define OBS_MANAGER_H

#include <windows.h>
#include <string>

class OBSManager {
public:
    OBSManager();
    ~OBSManager();

    bool initialize();
    void shutdown();

private:
    HMODULE hObs = nullptr;
    const std::string binPath = "C:\\ProyectoOBS\\bin\\64bit\\";
    const std::string dllPath = binPath + "obs.dll";

    // Prototipos de funciones de libobs
    typedef bool (*obs_startup_t)(const char*, void*, void*);
    typedef void (*obs_shutdown_t)(void);
};

#endif