console.log("Renderer script loaded successfully.");

// Wait for DOM to load.
console.log("Inside Renderer.js, top level.");

window.addEventListener('DOMContentLoaded', () => {
    const addRemappingButton = document.getElementById('add-remapping');
    const deleteRemappingButton = document.getElementById('delete-remapping');
    const viewRemappingButton = document.getElementById('view-remappings');
    const startHookButton = document.getElementById('start-hook');

    console.log("Inside renderer.js, addRemappingButton's value: ", addRemappingButton);

    if (addRemappingButton) {
        // Attach the event Listener to the button.
        addRemappingButton.addEventListener('click', () => {
            try {
                // // window.api.addRemapping();
                // const addRemapping = require('./scripts/components/addRemapping');
                // addRemapping(); // Call `addRemapping` without passing `window.api`

                console.log("addRemapping function in addRemapping.js is called.");

                const contentDiv = document.getElementById('content');

                contentDiv.innerHTML = `
                <h2>Add New Remapping</h2>
                <div>
                    <label for="application-select">Select Application</label>
                    <select id="application-select"></select>
                </div>

                <div>
                    <label for="original-key">Original Key</label>
                    <input type="text" id="original-key" placeholder="e.g., Ctrl+C" />
                </div>

                <div>
                    <label for="remapped key">Remapped Key:</label>
                    <input type="text" id="remapped-key" placeholder="e.g., Ctrl+Shift+P" />
                </div>

                <button id="submit-remapping">Add Remapping</button>

                <div id="feedback-message" style="margin-top: 10px;"></div>
            `;

                // Populating the dropdown list with running applications.
                const applicationSelect = document.getElementById('application-select');

                window.api.getRunningApplications().then((applications) => {
                    applications.forEach((app) => {
                        const option = document.createElement('option');

                        option.value = app.executableName;

                        option.textContent = `${app.executableName}`;

                        applicationSelect.appendChild(option);
                    });
                });


                // Adding event Listener to the "Add Remapping" Button.
                document.getElementById('submit-remapping').addEventListener('click', () => {
                    const application = applicationSelect.value;
                    const originalKey = document.getElementById('original-key').value;
                    const remappedKey = document.getElementById('remapped-key').value;
                    const feedbackMessage = document.getElementById('feedback-message');

                    // Clear previous messages.
                    feedbackMessage.textContent = '';
                    feedbackMessage.style.color = '';

                    if (!application || !originalKey || !remappedKey) {
                        feedbackMessage.textContent = 'Please fill in all fields.';
                        feedbackMessage.style.color = "red";

                        return;
                    };

                    window.api.addNewRemapping(application, originalKey, remappedKey).then((success) => {
                        if (success) {
                            feedbackMessage.textContent = `Successfully added remapping for ${originalKey} -> ${remappedKey} in ${application}.`;

                            feedbackMessage.style.color = 'green';
                        }

                        else {
                            feedbackMessage.textContent = 'Failed to add remapping.';

                            feedbackMessage.style.color = 'red';
                        }
                    }).catch((err) => {
                        console.error("Error adding remapping: ", err);

                        feedbackMessage.textContent = "An error occured while adding the remapping.";

                        feedbackMessage.style.color = 'red';
                    });
                });
            }

            catch (err) {
                console.log("Inside renderer.js (add remapping). Error: ", err);
            }
        });
    }

    else {
        console.error('Add Remapping Button not found in the DOM.');
    };



    if (deleteRemappingButton) {
        deleteRemappingButton.addEventListener('click', () => {
            try {
                const contentDiv = document.getElementById('content');

                contentDiv.innerHTML = `
                <h2>Delete Exisiting Remapping(s)</h2>
                <div>
                    <label for="application-select">Select Application</label>
                    <select id="application-select"></select>
                </div>

                <div>
                    <label for="original-key">Original Key</label>
                    <input type="text" id="original-key" placeholder="Please enter the key that is remapped.">
                </div>

                <button id="submit-remapping-deletion">Delete Remapping</button>

                <div id="feedback-message" style="margin-top: 10px;"></div>
                `;

                const applicationSelect = document.getElementById('application-select');

                window.api.getExecutableName().then((applications) => {
                    applications.forEach((app) => {
                        const option = document.createElement('option');

                        option.value = app.executableName;

                        option.textContent = `${app.executableName}`;

                        applicationSelect.appendChild(option);
                    });
                });


                document.getElementById('submit-remapping-deletion').addEventListener('click', () => {
                    const application = applicationSelect.value;
                    const originalKey = document.getElementById('original-key').value;
                    const feedbackMessage = document.getElementById('feedback-message');

                    feedbackMessage.textContent = '';
                    feedbackMessage.style.color = '';

                    if (!application || !originalKey) {
                        feedbackMessage.textContent = "Please fill in all the fields.";
                        feedbackMessage.style.color = "red";

                        return;
                    };

                    window.api.deleteRemapping(application, originalKey).then((success) => {
                        if (success) {
                            feedbackMessage.textContent = `Successfully deleted remapping of ${originalKey} for application -> ${application}`;

                            feedbackMessage.style.color = "green";
                        }

                        else {
                            feedbackMessage.textContent = "Failed to delete the remapping :(";

                            feedbackMessage.style.color = "red";
                        };
                    }).catch((err) => {
                        console.log("An Error error while trying to delete remapping. Error: ", err);

                        feedbackMessage.textContent = "Error while trying to delete remapping.";

                        feedbackMessage.style.color = "red";
                    });
                });
            }

            catch (err) {
                console.log("Inside renderer.js (delete remapping). Error: ", err);
            }
        });
    }

    else {
        console.error('Delete Remapping Button not found in the DOM.')
    }
 });