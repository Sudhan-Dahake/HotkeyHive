console.log("Renderer script loaded successfully.");

// Wait for DOM to load.
console.log("Inside Renderer.js, top level.");

window.addEventListener('DOMContentLoaded', () => {
    const addRemappingButton = document.getElementById('add-remapping');
    const deleteRemappingButton = document.getElementById('delete-remapping');
    const viewRemappingButton = document.getElementById('view-remappings');
    const hookButton = document.getElementById('hook');

    let isHookRunning = false;


    function populateApplicationDropdownForView(applicationSelect) {
        try {
            // Fetching all the remappings.
            return window.api.getAllRemappings().then((remappings) => {
                for (const application in remappings) {
                    const option = document.createElement('option');

                    option.value = application;

                    option.textContent = application;

                    applicationSelect.appendChild(option);
                }

                return remappings;
            });

            // const remappings = await window.api.getAllRemappings();

            // Object.keys(remappings).forEach((application) => {
            //     const option = document.createElement('option');

            //     option.value = application;

            //     option.textContent = application;

            //     applicationSelect.appendChild(option);
            // });

            // return remappings;
        }

        catch (err) {
            console.error("Error fetch remappings: ", err.message);

            return {};
        };
    };


    function populateRemappingsTableForView(remappingsTableBody, remappings, application) {
        remappingsTableBody.innerHTML = '';

        if ((!remappings[application]) || (remappings[application].length === 0)) {
            const noDataRow = document.createElement('tr');

            noDataRow.innerHTML = `
            <td colspan="2" style="text-align: center;">No remappings available</td>
            `;

            remappingsTableBody.appendChild(noDataRow);

            return;
        };


        remappings[application].forEach((remap) => {
            const row = document.createElement('tr');

            row.innerHTML = `
            <td>${remap.originalKey}</td>
            <td>${remap.remappedKey}</td>
            `;

            remappingsTableBody.appendChild(row);
        });
    }


    if (viewRemappingButton) {
        viewRemappingButton.addEventListener('click', () => {
            try {
                const contentDiv = document.getElementById('content');

                contentDiv.innerHTML = `
                <!-- Application Dropdown -->
                <div>
                    <label for="application-select">Select Application:</label>
                    <select id="application-select">
                        <option value="" disabled selected>Select an application</option>
                    </select>
                </div>

                <div id="remappings-container">
                    <table id="remappings-table">
                        <thead>
                            <tr>
                                <th>Original Key</th>
                                <th>Remapped Key</th>
                            </tr>
                        </thead>
                        <tbody>
                        </tbody>
                    </table>
                </div>
                `;

                const applicationSelect = document.getElementById('application-select');

                const remappingsTableBody = document.querySelector('#remappings-table tbody');


                populateApplicationDropdownForView(applicationSelect).then((remappings) => {
                    console.log(remappings);


                    applicationSelect.addEventListener('change', (event) => {
                        const selectedApplication = event.target.value;

                        console.log(selectedApplication);

                        populateRemappingsTableForView(remappingsTableBody, remappings, selectedApplication);
                    });
                });
            }

            catch (err) {
                console.log("Inside renderer.js, viewRemappingButton failed. Error: ", err.message);
            };
        });
    }


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

                applicationSelect.addEventListener('click', () => {
                    const currentValue = applicationSelect.value;

                    applicationSelect.innerHTML = '';

                    window.api.getRunningApplications().then((applications) => {
                        applications.forEach((app) => {
                            const option = document.createElement('option');

                            option.value = app.executableName;

                            option.textContent = `${app.executableName}`;

                            applicationSelect.appendChild(option);
                        });


                        if (applications.some((app) => app.executableName === currentValue)) {
                            applicationSelect.value = currentValue;
                        };
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


    if (hookButton) {
        hookButton.addEventListener('click', async () => {
            try {
                if (isHookRunning) {
                    isHookRunning = false;

                    await window.api.stopHook();

                    hookButton.innerText = "Start Hook";
                    hookButton.style.backgroundColor = "red";
                }

                else {
                    isHookRunning = true;

                    await window.api.startHook();

                    hookButton.innerText = "Stop Hook";
                    hookButton.style.backgroundColor = "#218838";
                }
            }

            catch (err) {
                console.error("Error while interacting with the button :( -- Error: ", err.message);
            };
        });
    }

    else {
        console.error('Hook Button not found in the DOM.')
    }
 });