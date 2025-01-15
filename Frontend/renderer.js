const addRemapping = require('./scripts/components/addRemapping');

// Attach the event listener to the "Add Remapping" button
document.getElementById('add-remapping').addEventListener('click', () => {
  addRemapping();
});