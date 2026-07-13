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

    void listSources();

private:
    HMODULE hObs = nullptr;

    const std::string binPath = "C:\\ProyectoOBS\\bin\\64bit\\";
    const std::string dllPath = binPath + "obs.dll";

    typedef bool (*obs_startup_t)(const char*, void*, void*);
    typedef void (*obs_shutdown_t)(void);

    typedef void (*obs_load_all_modules_t)(void);
    typedef void (*obs_post_load_modules_t)(void);

    typedef void (*obs_enum_sources_t)(void);

    obs_shutdown_t obs_shutdown = nullptr;
    obs_load_all_modules_t obs_load_all_modules = nullptr;
    obs_post_load_modules_t obs_post_load_modules = nullptr;
};

#endif
