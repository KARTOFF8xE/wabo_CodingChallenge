# Kinematics Visualisation

## Setup

1. Install Poetry (if not already):
   https://python-poetry.org/docs/#installation

2. Install dependencies:
   ```powershell
   poetry install
   ```

3. Make sure the kinematics FastAPI server is running at http://127.0.0.1:8000
   (see the kinematics server README for details)

## Running the Visualisation

Run the script with Poetry:
```powershell
poetry run python visualise.py
```

- This will open an interactive window showing the robot arm and its workspace.
- Use the sliders to adjust joint 0 and joint 1 angles.
- The arm and end effector (red point) will update live, using the kinematics server for calculations.

## Features
- Rectangle workspace (square, centered at (0,0), size = max(link lengths))
- Two-link robot arm, base at (0,0)
- Red point shows the end effector (cartesian position from the server)
- Sliders for joint_0 and joint_1
- Live update via FastAPI server

## Requirements
- Python 3.11+
- Poetry
- matplotlib, requests, numpy (installed via Poetry)
- Running kinematics server (see ../server/README.md)
