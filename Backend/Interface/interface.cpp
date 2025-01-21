#include "interface.h"

// BackendState* BackendState::instance = nullptr;

// // Define and initialize the static map
// std::map<std::string, std::vector<Remapping>> BackendState::appSpecificRemappings = {};

BackendState& BackendState::Instance() {

    static BackendState instance;

    return instance;
}

// std::map<std::string, std::vector<Remapping>> BackendState::GetRemappingsInternally() {
//     return GetAllRemappings();
// };

// Function to initialize the backend (i.e., Load remapping from file).
void BackendState::InitializeBackendForGUI(std::map<std::string, std::vector<Remapping>>* appSpecificRemappings) {
    LoadRemappingsFromFile(&appSpecificRemappings, FILENAME);

    // this->backendMutex.lock();

    // return this->GetRemappingsInternally();

    // this->backendMutex.unlock();

    // std::cout << "Address of map inside InitializeBackendForGUI: " << &this->appSpecificRemappings << std::endl;

    // Iterate through the map
    // for (const auto &[application, remappings] : this->appSpecificRemappings)
    // {
    //     std::cout << "Application: " << application << std::endl;

    //     // Iterate through the vector of remappings for the current application
    //     for (const auto &remapping : remappings)
    //     {
    //         std::cout << "  Original Key: " << remapping.originalKey
    //                   << " -> Remapped Key: " << remapping.remappedKey << std::endl;
    //     }
    // }
};

// Function to add a new key remapping.
bool BackendState::AddNewRemappingForGUI(std::map<std::string, std::vector<Remapping>>* appSpecificRemappings, const std::string &application, const std::string &originalKey, const std::string &remappedKey)
{
    try {
        std::cout << "Address of map inside AddNewRemappingForGUI: " << appSpecificRemappings << std::endl;
        // Check if the map is empty
        if ((*appSpecificRemappings).empty())
        {
            std::cout << "No remappings available." << std::endl;
            // return false;
        }

        // Iterate through the map
        for (const auto &[application, remappings] : *appSpecificRemappings)
        {
            std::cout << "Application: " << application << std::endl;

            // Iterate through the vector of remappings for the current application
            for (const auto &remapping : remappings)
            {
                std::cout << "  Original Key: " << remapping.originalKey
                          << " -> Remapped Key: " << remapping.remappedKey << std::endl;
            }
        }

        bool success = AddKeyRemapping(&appSpecificRemappings, application, originalKey, remappedKey);

        if (success) {
            SaveRemappingsForGUI(appSpecificRemappings);
        };

        return success;
    }

    catch (const std::exception& e) {
        std::cerr << "Error adding remapping: " << e.what() << std::endl;

        return false;
    };
};

// // Function to retrieve all remappings.
// std::map<std::string, std::vector<Remapping>> BackendState::GetAllRemappingForGUI() {
//     return this->appSpecificRemappings;
// };


// function to delete a specific remapping.
bool BackendState::DeleteRemappingForGUI(std::map<std::string, std::vector<Remapping>>* appSpecificRemappings, const std::string &application, const std::string &originalKey) {
    // auto& appSpecificRemappings = GetAllRemappings();

    // Checking to see if the application exists in the map.
    if ((*appSpecificRemappings).find(application) != (*appSpecificRemappings).end()) {
        auto& remappings = (*appSpecificRemappings)[application];

        // Find the remapping in the vector.
        auto it = std::remove_if(remappings.begin(), remappings.end(),
                                 [&originalKey](const Remapping &remapping) {
                                    return remapping.originalKey == originalKey;
                                 });

        if (it != remappings.end()) {
            remappings.erase(it, remappings.end());   // Erasing hte matched remapping.

            // If no remappings are left for the application then remove the application entry.
            if (remappings.empty()) {
                (*appSpecificRemappings).erase(application);
            };

            return true;        // Remapping deleted successfully.
        };
    };

    return false;         // Remapping not found.
};



// Function to save remappings to the file.
void BackendState::SaveRemappingsForGUI(std::map<std::string, std::vector<Remapping>>* appSpecificRemappings)
{
    SaveRemappingsToFile(&appSpecificRemappings, FILENAME);
};

// Function to get the currently running applications.
std::vector<ApplicationInfo> BackendState::GetRunningApplicationsForGUI() {
    return GetRunningApplications();
};


// Function to start the keyboard hook.
void BackendState::StartKeyboardHookForGUI() {
    InstallKeyboardHook();

    MSG msg;

    // Message loop to keep the hook alive.
    while (!exitProgram)
    {
      if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
      {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
      }
    }

    // Cleanup -> Removing the hook.
    RemoveKeyboardHook();

    exitProgram = false;
};


// Function to gracefully shut down the backend.
void BackendState::ShutdownBackendForGUI(std::map<std::string, std::vector<Remapping>>* appSpecificRemappings) {
    this->SaveRemappingsForGUI(appSpecificRemappings);
};