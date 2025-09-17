
# Wandelbots Coding Challenge

The goal is to improve the existing implementation so that the visualization can work without performing its own forward kinematics calculation.

## Project Structure

- `kinematics/`: C++ library for kinematics calculations
- `server/`: Python FastAPI server exposing the kinematics API
- `visualisation/`: Python visualization client that interacts with the server

## Tasks

1. **Extend the WaBo API &rarr; Done**
	Add a new endpoint that allows the visualization to request forward kinematics results from the server, so the visualization does not need to compute it itself.

2. **Update the API Definition &rarr; Done**
	Modify `api/openapi.yaml` to include the new endpoint.

3. **Regenerate the Server &rarr; Done**
	Use the OpenAPI code generation tool to regenerate the FastAPI server code with the new endpoint.

4. **Implement the Endpoint in the Server &rarr; Done**
	Add the logic for the new endpoint in the FastAPI server (`kinematics_server`).

5. **Implement the Function in the Kinematics Library**
	Add a corresponding function in the C++ kinematics library, and create a meaningful test for it in `kinematics/tests/kinematics_test.cpp`.

6. **If you have time left, what would be a beneficial task to improve the maintenance of the project &rarr; Done (partially)**
	Depending on the time you have left, write down what you would do, and if you still have time, do it.


# Georgs solution

## Get Started:
* `cd kinematics`
* `mkdir build`
* `cd build`
* `cmake .. && make`
* `mkdir -p ../../server/kinematics/lib`
* `cp libwb_kinematics_shared.so ../../server/kinematics/lib`
* `cd ../../server`
* `poetry install`
* `poetry run uvicorn kinematics_server.main:app --reload`
* goto `http://127.0.0.1:8000/`
* try it out :) (you can also try it within the visualization directly, look inside the `visualization/Readme.md` for more information)
* to execute the tests, go back to the `build` directory and execute .`/tests/kinematic_test`

## Times:
* received: 10:00
* install poetry and got a look onto the repo and fixed some small bugs (missing pks): 10:00-10:15
* Tasks 1-4 and 6: 10:15-11:31
* Writing Readme: 11:32 - ...
* Task 5 (edited Task 6) and implemented new API to visualization: 15:55-16:15

## Additional Tasks:
* ensure the angles are radiant (kinematics/src/joint.cpp)
* add installing .so via CMake (move/cpy .so to correct location), add install and start script
* add option for multiple animations (parameters for endpoint (in openapi.yaml))
* take a look if the exemplary API-values are realistic
* add to GitHub and write .gitignore, ...
* some more fault detection or even tolerance

## Workflow:
1) included cmath for cos, sin, ...
2) cmake .. and make in kinematics/build and move .so to server/kinematics/lib
3) start server as described in server/readme.md
4) modified openapi.yml
5) restarted server as in 3.
6) implemented computations
7) restarted server as in 3.
8) going to write Readme.md now :)
9) Edited