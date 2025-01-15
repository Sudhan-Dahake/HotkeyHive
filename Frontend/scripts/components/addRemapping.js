const backend = require('../../../native_backend/build/Release/backend.node');

function addRemapping() {
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
  const applications = backend.getRunningApplications();

  applications.forEach(app => {
    const option = document.createElement('option');
    option.value = app.executableName;
    option.textContent = `${app.windowTitle} (${app.executableName})`;
    applicationSelect.appendChild(option);
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

    try {
      const success = backend.addNewRemapping(application, originalKey, remappedKey);

      console.log(success);

      if (success) {
        feedbackMessage.textContent = `Successfully added remapping for ${originalKey} -> ${remappedKey} in ${application}.`

        feedbackMessage.style.color = "green";
      }

      else {
        feedbackMessage.textContent = "Failed to add remapping.";

        feedbackMessage.style.color = "red";
      }
    }

    catch (err) {
      console.error(err);

      feedbackMessage.textContent = "An error occurred while adding the remapping.";

      feedbackMessage.style.color = "red";
    }
  });
}

module.exports = addRemapping;