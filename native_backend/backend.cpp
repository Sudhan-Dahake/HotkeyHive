#include <napi.h>
#include "../Backend/Interface/interface.h"

std::map<std::string, std::vector<Remapping>> appSpecificRemappings = {};

// Initialize Backend.
Napi::Value InitializeBackendExpose(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    // Access the singleton instance.
    BackendState* backend = BackendState::Instance();

    std::cout << "Backend address: " << backend << std::endl;

    // Load remappings from the file.
    backend->InitializeBackendForGUI();

    return env.Undefined();
};


// Exposing AddKeyRemapping function.
Napi::Value AddNewRemappingExpose(const Napi::CallbackInfo& info) {
    std::cout << "Hello World inside AddNewRemappingExpose." << std::endl;

    Napi::Env env = info.Env();

    std::cout << "Before strings are checked if they are actually strings or not." << std::endl;

    if ((info.Length() != 3) || (!info[0].IsString()) || (!info[1].IsString()) || (!info[2].IsString())) {
        Napi::TypeError::New(env, "Expected three string arguments").ThrowAsJavaScriptException();

        return env.Null();
    };

    std::cout << "Before strings are converted" << std::endl;

    // Get parameters from javascript.
    std::string application = info[0].As<Napi::String>();
    std::string originalKey = info[1].As<Napi::String>();
    std::string remappedKey = info[2].As<Napi::String>();

    std::cout << "After strings are converted" << std::endl;

    try {

        std::cout << "Accessed the AddNewRemappingExpose!!" << std::endl;
        // Access the singleton instance
        BackendState* backend = BackendState::Instance();

        std::cout << "Backend address: " << backend << std::endl;

        // Calling the backend function.
        bool success = backend->AddNewRemappingForGUI(application, originalKey, remappedKey);

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

    // Access the singleton instance
    BackendState* backend = BackendState::Instance();

    const auto &remappings = backend->GetAllRemappingForGUI();

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
    BackendState* backend = BackendState::Instance();

    bool success = backend->DeleteRemappingForGUI(application, originalKey);

    return Napi::Boolean::New(env, success);
};


// Save Remappings.
Napi::Value SaveRemappingsExpose(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();

    // Access the singleton instance
    BackendState* backend = BackendState::Instance();

    backend->SaveRemappingsForGUI();

    return env.Undefined();
};


// Get Running Applications.
Napi::Value GetRunningApplicationsExpose(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    // Access the singleton instance
    BackendState* backend = BackendState::Instance();

    auto applications = backend->GetRunningApplicationsForGUI();

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
    BackendState* backend = BackendState::Instance();

    backend->StartKeyboardHookForGUI();

    return env.Undefined();
};


// Shutdown Backend.
Napi::Value ShutdownBackendExpose(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();

    // Access the singleton instance
    BackendState* backend = BackendState::Instance();

    backend->ShutdownBackendForGUI();

    return env.Undefined();
};


// Module Initialization.
Napi::Object Init(Napi::Env env, Napi::Object exports) {
    // Exposing backend functions to JavaScript.
    exports.Set("initializeBackend", Napi::Function::New(env, InitializeBackendExpose));
    exports.Set("addNewRemapping", Napi::Function::New(env, AddNewRemappingExpose));
    exports.Set("getAllRemappings", Napi::Function::New(env, GetAllRemappingsExpose));
    exports.Set("deleteRemapping", Napi::Function::New(env, DeleteRemappingExpose));
    exports.Set("saveRemappings", Napi::Function::New(env, SaveRemappingsExpose));
    exports.Set("getRunningApplications", Napi::Function::New(env, GetRunningApplicationsExpose));
    exports.Set("startKeyboardHook", Napi::Function::New(env, StartKeyboardHookExpose));
    exports.Set("shutdownBackend", Napi::Function::New(env, ShutdownBackendExpose));

    return exports; // Return the exported functions.
}

// Register the module with Node.js.
NODE_API_MODULE(backend, Init)