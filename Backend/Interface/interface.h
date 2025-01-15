#include "../keyboard_hook/keyboard_hook.h"
#include "../key_remapper/key_remapper.h"
#include "../utils/utils.h"
#include <iostream>
#include <algorithm>
#include <memory>
#include <mutex>

#define FILENAME "remappings.txt"

class BackendState {
    // static BackendState& instance;

    // static std::map<std::string, std::vector<Remapping>> appSpecificRemappings;

    BackendState() = default;

    std::map<std::string, std::vector<Remapping>> GetRemappingsInternally();

    // std::mutex backendMutex;

  public:
    static BackendState& Instance();

    BackendState(const BackendState&) = delete;
    BackendState& operator=(const BackendState &) = delete;

    // Function to initialize the backend (i.e., Load remapping from file).
    std::map<std::string, std::vector<Remapping>> InitializeBackendForGUI();

    // Function to add a new key remapping.
    bool AddNewRemappingForGUI(const std::string &application, const std::string &originalKey, const std::string &remappedKey);

    // Function to retrieve all remappings.
    std::map<std::string, std::vector<Remapping>> GetAllRemappingForGUI();

    // function to delete a specific remapping.
    bool DeleteRemappingForGUI(const std::string &application, const std::string &originalKey);

    // Function to save remappings to the file.
    void SaveRemappingsForGUI();

    // Function to get the currently running applications.
    std::vector<ApplicationInfo> GetRunningApplicationsForGUI();

    // Function to start the keyboard hook.
    void StartKeyboardHookForGUI();

    // Function to gracefully shut down the backend.
    void ShutdownBackendForGUI();
};
