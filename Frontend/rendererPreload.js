const { contextBridge, ipcRenderer } = require('electron');
// const path = require('path');
// const addRemapping = require(path.join(__dirname, 'scripts', 'components', 'addRemapping'));

console.log('Preload script loaded.');

// contextBridge.exposeInMainWorld('addRemapping', (api) => addRemapping(api));

contextBridge.exposeInMainWorld('api', {
    // addRemapping: (api) => ipcRenderer.invoke('add-remapping', api),
    getRunningApplications: () => ipcRenderer.invoke('get-running-applications'),
    getAllRemappings: () => ipcRenderer.invoke('get-all-remappings'),
    addNewRemapping: (application, originalKey, remappedKey) => ipcRenderer.invoke('add-new-remapping', { application, originalKey, remappedKey }),
    getExecutableName: () => ipcRenderer.invoke('get-executable-name'),
    deleteRemapping: (application, originalKey) => ipcRenderer.invoke('delete-remapping', { application, originalKey }),
    startHook: () => ipcRenderer.invoke('start-hook'),
    stopHook: () => ipcRenderer.invoke('stop-hook'),
});