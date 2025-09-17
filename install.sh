#!/bin/bash

cd kinematics
mkdir build
cd build
cmake .. && make
mkdir -p ../../server/kinematics/lib
cp libwb_kinematics_shared.so ../../server/kinematics/lib
cd ../../server
poetry install