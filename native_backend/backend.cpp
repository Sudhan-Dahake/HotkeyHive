#include <napi.h>
#include "../Backend/Interface/interface.h"

// std::map<std::string, std::vector<Remapping>> appSpecificRemappings = {};

// bool oneTimeLoadRemappingsForAddNewRemappingExpose = true;

// // Initialize Backend.
// Napi::Value InitializeBackendExpose(const Napi::CallbackInfo &info) {
//     Napi::Env env = info.Env();

//     // Access the singleton instance.
//     BackendState& backend = BackendState::Instance();

//     std::cout << "Backend address: " << &backend << std::endl;

//     std::cout << std::endl << "appSpecificRemapping address inside InitializeBackendExpose: " << &appSpecificRemappings << std::endl;

//     // Load remappings from the file.
//     backend.InitializeBackendForGUI(&appSpecificRemappings);

//     // Check if the map is empty
//     if ((appSpecificRemappings).empty())
//     {
//         std::cout << "No remappings available inside InitializeBackendExpose." << std::endl;
//     }

//     else {
//         std::cout << "Remappings are loaded successfully inside the map and displayed below: " << std::endl;
//     }

//     for (const auto &[application, remappings] : appSpecificRemappings)
//     {
//         std::cout << "Application: " << application << std::endl;

//         // Iterate through the vector of remappings for the current application
//         for (const auto &remapping : remappings)
//         {
//             std::cout << "  Original Key: " << remapping.originalKey
//                       << " -> Remapped Key: " << remapping.remappedKey << std::endl;
//         }
//     }

//     return env.Undefined();
// };

// // Exposing AddKeyRemapping function.
// Napi::Value AddNewRemappingExpose(const Napi::CallbackInfo& info) {
//     std::cout << "Hello World inside AddNewRemappingExpose." << std::endl;

//     Napi::Env env = info.Env();

//     if ((info.Length() != 3) || (!info[0].IsString()) || (!info[1].IsString()) || (!info[2].IsString())) {
//         Napi::TypeError::New(env, "Expected three string arguments").ThrowAsJavaScriptException();

//         return env.Null();
//     };

//     // Get parameters from javascript.
//     std::string application = info[0].As<Napi::String>();
//     std::string originalKey = info[1].As<Napi::String>();
//     std::string remappedKey = info[2].As<Napi::String>();

//     try {
//         std::cout << "Accessed the AddNewRemappingExpose!!" << std::endl;
//         // Access the singleton instance
//         BackendState& backend = BackendState::Instance();

//         if (oneTimeLoadRemappingsForAddNewRemappingExpose) {
//             // Load remappings from the file.
//             backend.InitializeBackendForGUI(&appSpecificRemappings);

//             oneTimeLoadRemappingsForAddNewRemappingExpose = false;
//         };

//         std::cout << "Backend address: " << &backend << std::endl;

//         std::cout << std::endl << "appSpecificRemapping address inside AddNewRemappingExpose: " << &appSpecificRemappings << std::endl;

//         // Check if the map is empty
//         if ((appSpecificRemappings).empty())
//         {
//             std::cout << "No remappings available inside AddNewRemappingExpose." << std::endl;
//         }

//         else
//         {
//             std::cout << "Remappings are loaded successfully inside the map and displayed below: " << std::endl;
//         }

//         for (const auto &[application, remappings] : appSpecificRemappings)
//         {
//             std::cout << "Application: " << application << std::endl;

//             // Iterate through the vector of remappings for the current application
//             for (const auto &remapping : remappings)
//             {
//                 std::cout << "  Original Key: " << remapping.originalKey
//                           << " -> Remapped Key: " << remapping.remappedKey << std::endl;
//             }
//         }

//         // Calling the backend function.
//         bool success = backend.AddNewRemappingForGUI(&appSpecificRemappings, application, originalKey, remappedKey);

//         return Napi::Boolean::New(env, success);
//     }

//     catch (const std::exception& e) {
//         Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();

//         return env.Null();
//     };
// };


// // Get All Remappings.
// Napi::Value GetAllRemappingsExpose(const Napi::CallbackInfo& info) {
//     Napi::Env env = info.Env();

//     const auto &remappings = appSpecificRemappings;

//     Napi::Object result = Napi::Object::New(env);

//     for(const auto& [application, remapList] : remappings) {
//         Napi::Array remapArray = Napi::Array::New(env, remapList.size());

//         for (size_t i = 0; i < remapList.size(); i++) {
//             Napi::Object remapObj = Napi::Object::New(env);

//             remapObj.Set("originalKey", remapList[i].originalKey);
//             remapObj.Set("remappedKey", remapList[i].remappedKey);
//             remapArray[i] = remapObj;
//         };

//         result.Set(application, remapArray);
//     };

//     return result;
// };



// // Delete Remapping.
// Napi::Value DeleteRemappingExpose(const Napi::CallbackInfo &info) {
//     Napi::Env env = info.Env();

//     if ((info.Length() != 2) || (!info[0].IsString()) || (!info[1].IsString())) {
//         Napi::TypeError::New(env, "Expected two string arguments").ThrowAsJavaScriptException();

//         return env.Null();
//     };

//     std::string application = info[0].As<Napi::String>();
//     std::string originalKey = info[1].As<Napi::String>();

//     // Access the singleton instance
//     BackendState& backend = BackendState::Instance();

//     bool success = backend.DeleteRemappingForGUI(&appSpecificRemappings, application, originalKey);

//     return Napi::Boolean::New(env, success);
// };


// // Save Remappings.
// Napi::Value SaveRemappingsExpose(const Napi::CallbackInfo& info) {
//     Napi::Env env = info.Env();

//     // Access the singleton instance
//     BackendState& backend = BackendState::Instance();

//     backend.SaveRemappingsForGUI(&appSpecificRemappings);

//     return env.Undefined();
// };


// // Get Running Applications.
// Napi::Value GetRunningApplicationsExpose(const Napi::CallbackInfo &info) {
//     Napi::Env env = info.Env();

//     // Access the singleton instance
//     BackendState& backend = BackendState::Instance();

//     auto applications = backend.GetRunningApplicationsForGUI();

//     Napi::Array result = Napi::Array::New(env, applications.size());

//     for (size_t i = 0; i < applications.size(); i++) {
//         Napi::Object appObj = Napi::Object::New(env);

//         appObj.Set("windowTitle", applications[i].windowTitle);
//         appObj.Set("executableName", applications[i].executableName);

//         result[i] = appObj;
//     };

//     return result;
// };


// // Start Keyboard Hook.
// Napi::Value StartKeyboardHookExpose(const Napi::CallbackInfo &info) {
//     Napi::Env env = info.Env();

//     // Access the singleton instance
//     BackendState& backend = BackendState::Instance();

//     backend.StartKeyboardHookForGUI();

//     return env.Undefined();
// };


// // Shutdown Backend.
// Napi::Value ShutdownBackendExpose(const Napi::CallbackInfo &info) {
//     Napi::Env env = info.Env();

//     // Access the singleton instance
//     BackendState& backend = BackendState::Instance();

//     backend.ShutdownBackendForGUI(&appSpecificRemappings);

//     return env.Undefined();
// };


// // Module Initialization.
// Napi::Object Init(Napi::Env env, Napi::Object exports) {
//     // Exposing backend functions to JavaScript.
//     exports.Set("initializeBackend", Napi::Function::New(env, InitializeBackendExpose));
//     exports.Set("addNewRemapping", Napi::Function::New(env, AddNewRemappingExpose));
//     exports.Set("getAllRemappings", Napi::Function::New(env, GetAllRemappingsExpose));
//     exports.Set("deleteRemapping", Napi::Function::New(env, DeleteRemappingExpose));
//     exports.Set("saveRemappings", Napi::Function::New(env, SaveRemappingsExpose));
//     exports.Set("getRunningApplications", Napi::Function::New(env, GetRunningApplicationsExpose));
//     exports.Set("startKeyboardHook", Napi::Function::New(env, StartKeyboardHookExpose));
//     exports.Set("shutdownBackend", Napi::Function::New(env, ShutdownBackendExpose));

//     return exports; // Return the exported functions.
// }

// // Register the module with Node.js.
// NODE_API_MODULE(backend, Init)














class BackendHandler {
    std::map<std::string, std::vector<Remapping>> appSpecificRemappings;

    // Private constructor to prevent direct instantiation.
    BackendHandler() = default;

public:
    static BackendHandler& Instance() {
        static BackendHandler instance;     // A single shared instance.

        return instance;
    };

    BackendHandler(const BackendHandler&) = delete;

    BackendHandler &operator=(const BackendHandler&) = delete;

    // Initialize Backend.
    Napi::Value InitializeBackendExpose(const Napi::CallbackInfo &info) {
        Napi::Env env = info.Env();

        // Access the singleton instance.
        BackendState& backend = BackendState::Instance();

        std::cout << "Backend address: " << &backend << std::endl;

        std::cout << std::endl << "appSpecificRemapping address inside InitializeBackendExpose: " << &appSpecificRemappings << std::endl;

        // Load remappings from the file.
        backend.InitializeBackendForGUI(&appSpecificRemappings);

        // Check if the map is empty
        if ((appSpecificRemappings).empty())
        {
            std::cout << "No remappings available inside InitializeBackendExpose." << std::endl;
        }

        else {
            std::cout << "Remappings are loaded successfully inside the map and displayed below: " << std::endl;
        }

        for (const auto &[application, remappings] : appSpecificRemappings)
        {
            std::cout << "Application: " << application << std::endl;

            // Iterate through the vector of remappings for the current application
            for (const auto &remapping : remappings)
            {
                std::cout << "  Original Key: " << remapping.originalKey
                        << " -> Remapped Key: " << remapping.remappedKey << std::endl;
            }
        }

        return env.Undefined();
    };


    // Exposing AddKeyRemapping function.
    Napi::Value AddNewRemappingExpose(const Napi::CallbackInfo& info) {
        std::cout << "Hello World inside AddNewRemappingExpose." << std::endl;

        Napi::Env env = info.Env();

        if ((info.Length() != 3) || (!info[0].IsString()) || (!info[1].IsString()) || (!info[2].IsString())) {
            Napi::TypeError::New(env, "Expected three string arguments").ThrowAsJavaScriptException();

            return env.Null();
        };

        // Get parameters from javascript.
        std::string application = info[0].As<Napi::String>();
        std::string originalKey = info[1].As<Napi::String>();
        std::string remappedKey = info[2].As<Napi::String>();

        try {
            std::cout << "Accessed the AddNewRemappingExpose!!" << std::endl;
            // Access the singleton instance
            BackendState& backend = BackendState::Instance();

            // if (oneTimeLoadRemappingsForAddNewRemappingExpose) {
            //     // Load remappings from the file.
            //     backend.InitializeBackendForGUI(&appSpecificRemappings);

            //     oneTimeLoadRemappingsForAddNewRemappingExpose = false;
            // };

            std::cout << "Backend address: " << &backend << std::endl;

            std::cout << std::endl << "appSpecificRemapping address inside AddNewRemappingExpose: " << &appSpecificRemappings << std::endl;

            // Check if the map is empty
            if ((appSpecificRemappings).empty())
            {
                std::cout << "No remappings available inside AddNewRemappingExpose." << std::endl;
            }

            else
            {
                std::cout << "Remappings are loaded successfully inside the map and displayed below: " << std::endl;
            }

            for (const auto &[application, remappings] : appSpecificRemappings)
            {
                std::cout << "Application: " << application << std::endl;

                // Iterate through the vector of remappings for the current application
                for (const auto &remapping : remappings)
                {
                    std::cout << "  Original Key: " << remapping.originalKey
                            << " -> Remapped Key: " << remapping.remappedKey << std::endl;
                }
            }

            // Calling the backend function.
            bool success = backend.AddNewRemappingForGUI(&appSpecificRemappings, application, originalKey, remappedKey);

            return Napi::Boolean::New(env, success);
        }

        catch (const std::exception& e) {
            Napi::Error::New(env, e.what()).ThrowAsJavaScriptException();

            return env.Null();
        };
    };


    // Get All Remappings.
    Napi::Value GetAllRemappingsExpose(const Napi::CallbackInfo& info) {
        Napi::Env env = info.Env();

        const auto &remappings = appSpecificRemappings;

        Napi::Object result = Napi::Object::New(env);

        for(const auto& [application, remapList] : remappings) {
            Napi::Array remapArray = Napi::Array::New(env, remapList.size());

            for (size_t i = 0; i < remapList.size(); i++) {
                Napi::Object remapObj = Napi::Object::New(env);

                remapObj.Set("originalKey", remapList[i].originalKey);
                remapObj.Set("remappedKey", remapList[i].remappedKey);
                remapArray[i] = remapObj;
            };

            result.Set(application, remapArray);
        };

        return result;
    };



    // Delete Remapping.
    Napi::Value DeleteRemappingExpose(const Napi::CallbackInfo &info) {
        Napi::Env env = info.Env();

        if ((info.Length() != 2) || (!info[0].IsString()) || (!info[1].IsString())) {
            Napi::TypeError::New(env, "Expected two string arguments").ThrowAsJavaScriptException();

            return env.Null();
        };

        std::string application = info[0].As<Napi::String>();
        std::string originalKey = info[1].As<Napi::String>();

        // Access the singleton instance
        BackendState& backend = BackendState::Instance();

        bool success = backend.DeleteRemappingForGUI(&appSpecificRemappings, application, originalKey);

        return Napi::Boolean::New(env, success);
    };


    // Save Remappings.
    Napi::Value SaveRemappingsExpose(const Napi::CallbackInfo& info) {
        Napi::Env env = info.Env();

        // Access the singleton instance
        BackendState& backend = BackendState::Instance();

        backend.SaveRemappingsForGUI(&appSpecificRemappings);

        return env.Undefined();
    };


    // Get Running Applications.
    Napi::Value GetRunningApplicationsExpose(const Napi::CallbackInfo &info) {
        Napi::Env env = info.Env();

        // Access the singleton instance
        BackendState& backend = BackendState::Instance();

        auto applications = backend.GetRunningApplicationsForGUI();

        Napi::Array result = Napi::Array::New(env, applications.size());

        for (size_t i = 0; i < applications.size(); i++) {
            Napi::Object appObj = Napi::Object::New(env);

            appObj.Set("windowTitle", applications[i].windowTitle);
            appObj.Set("executableName", applications[i].executableName);

            result[i] = appObj;
        };

        return result;
    };


    // Start Keyboard Hook.
    Napi::Value StartKeyboardHookExpose(const Napi::CallbackInfo &info) {
        Napi::Env env = info.Env();

        // Access the singleton instance
        BackendState& backend = BackendState::Instance();

        backend.StartKeyboardHookForGUI();

        return env.Undefined();
    };


    // Shutdown Backend.
    Napi::Value ShutdownBackendExpose(const Napi::CallbackInfo &info) {
        Napi::Env env = info.Env();

        // Access the singleton instance
        BackendState& backend = BackendState::Instance();

        backend.ShutdownBackendForGUI(&appSpecificRemappings);

        return env.Undefined();
    };
};


// Module Initialization.
Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
    BackendHandler& backendHandler = BackendHandler::Instance();

    // Exposing backend functions to JavaScript.
    exports.Set("initializeBackend", Napi::Function::New(env, [&backendHandler](const Napi::CallbackInfo& info) {
        return backendHandler.InitializeBackendExpose(info);
    }));

    // Exposing backend functions to JavaScript.
    exports.Set("addNewRemapping", Napi::Function::New(env, [&backendHandler](const Napi::CallbackInfo& info) {
        return backendHandler.AddNewRemappingExpose(info);
    }));

    // Exposing backend functions to JavaScript.
    exports.Set("getAllRemappings", Napi::Function::New(env, [&backendHandler](const Napi::CallbackInfo& info) {
        return backendHandler.GetAllRemappingsExpose(info);
    }));

    // Exposing backend functions to JavaScript.
    exports.Set("deleteRemapping", Napi::Function::New(env, [&backendHandler](const Napi::CallbackInfo& info) {
        return backendHandler.DeleteRemappingExpose(info);
    }));

    // Exposing backend functions to JavaScript.
    exports.Set("saveRemappings", Napi::Function::New(env, [&backendHandler](const Napi::CallbackInfo& info) {
        return backendHandler.SaveRemappingsExpose(info);
    }));

    // Exposing backend functions to JavaScript.
    exports.Set("getRunningApplications", Napi::Function::New(env, [&backendHandler](const Napi::CallbackInfo& info) {
        return backendHandler.GetRunningApplicationsExpose(info);
    }));

    // Exposing backend functions to JavaScript.
    exports.Set("startKeyboardHook", Napi::Function::New(env, [&backendHandler](const Napi::CallbackInfo& info) {
        return backendHandler.StartKeyboardHookExpose(info);
    }));

            // Exposing backend functions to JavaScript.
    exports.Set("shutdownBackend", Napi::Function::New(env, [&backendHandler](const Napi::CallbackInfo& info) {
        return backendHandler.ShutdownBackendExpose(info);
    }));

    return exports; // Return the exported functions.
};

// Register the module with Node.js.
NODE_API_MODULE(backend, InitAll)