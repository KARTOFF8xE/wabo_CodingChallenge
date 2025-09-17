# Kinematics FastAPI Server

## Setup

1. Install Poetry (if not already):
   https://python-poetry.org/docs/#installation

2. Install dependencies:
   ```powershell
   poetry install
   ```

3. Build your C++ kinematics shared library so that `wb_kinematics_shared.dll` (or `.so`/`.dylib`) is present in `server/kinematics/lib`.

4. Generate FastAPI server code from `api/openapi.yaml` (see below).

5. Run the server:
   ```powershell
   poetry run uvicorn kinematics_server.main:app --reload
   ```

6. See the api at: http://127.0.0.1:8000


## OpenAPI code generation


Recommended: Use `fastapi-codegen` to generate FastAPI server code from your OpenAPI spec.

- Generate FastAPI server code:
  ```powershell
  poetry run fastapi-codegen --input ../api/openapi.yaml --output kinematics_server --model-file models.py
  ```

## C library binding

- The server will use `cffi` to load and call functions from `wb_kinematics_shared`.
- Place the shared library in `server/kinematics/lib`.
- See `kinematics_server/kinematics_cffi.py` for the binding stub.
