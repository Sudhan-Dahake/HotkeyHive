const { app, BrowserWindow, ipcMain } = require('electron');
const backend = require('../native_backend/build/Release/backend.node');

let mainWindow;

app.on('ready', () => {
    // Call the backend initialization function.
    try {
        backend.initializeBackend();

        console.log('Backend initialized successfully.');
    }

    catch (err) {
        console.error("Failed to initialize the backend: ", err.message);
    }

    mainWindow = new BrowserWindow({
        width: 800,
        height: 600,
        webPreferences: {
            nodeIntegration: true,
            contextIsolation: false,
        },
    });

    mainWindow.loadFile('index.html');
});


app.on('window-all-closed', () => {
    if (process.platform !== 'darwin') {
        app.quit();
    }
});