const { app, BrowserWindow, ipcMain } = require('electron');
const backend = require('../native_backend/build/Release/backend.node');

let mainWindow;

app.on('ready', () => {
    mainWindow = new BrowserWindow({
        width: 800,
        height: 600,
        webPreferences: {
            preload: __dirname + '/rendererPreload.js',
            contextIsolation: true,
        },
    });

    mainWindow.loadFile('index.html');

    mainWindow.webContents.openDevTools();

    // Call the backend initialization function.
    try {
        backend.initializeBackend();

        console.log('Backend initialized successfully. Hello');
    }

    catch (err) {
        console.error("Failed to initialize the backend: ", err.message);
    }
});


// // Handling IPC call to execute addRemapping logic.
// ipcMain.handle('add-remapping', async (_, { application, originalKey, remappedKey }) => {
//     try {
//         const result = addRemapping(application, originalKey, remappedKey);

//         return { success: result };
//     }

//     catch (error) {
//         console.error('Failed to add remappings: ', error);

//         return { success: false, error: error.message };
//     };
// });


ipcMain.handle('get-running-applications', async () => {
    try {
        return backend.getRunningApplications();
    }

    catch (err) {
        console.error('Failed to get running applications: ', err.message);

        throw err;
    };
});


ipcMain.handle('add-new-remapping', async (event, { application, originalKey, remappedKey }) => {
    try {
        return backend.addNewRemapping(application, originalKey, remappedKey);
    }

    catch (err) {
        console.error('Failed to add remapping: ', err.message);

        throw err;
    }
});


app.on('window-all-closed', () => {
    if (process.platform !== 'darwin') {
        app.quit();
    }
});