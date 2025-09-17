import cffi
import os
import sys

# Find the shared library (DLL/SO/DYLIB)
if sys.platform.startswith("win"):
    libname = "wb_kinematics_shared.dll"
elif sys.platform == "darwin":
    libname = "libwb_kinematics_shared.dylib"
else:
    libname = "libwb_kinematics_shared.so"

libpath = os.path.join(os.path.dirname(__file__), "..", "kinematics", "lib", libname)

ffi = cffi.FFI()
ffi.cdef("""
typedef struct {
    unsigned int major;
    unsigned int minor;
    unsigned int patch;
} kinematics_version_t;

typedef struct {
    float length_0;
    float length_1;
} kinematics_link_lengths_t;

typedef struct {
    float x;
    float y;
} kinematics_cartesian_position_t;

typedef struct {
    float joint_0;
    float joint_1;
} kinematics_joint_position_t;

typedef struct {
    float x0;
    float x1;
    float x2;
    float y0;
    float y1;
    float y2;
    float xpos;
    float ypos;
} kinematics_full_results_t;

const kinematics_version_t kinematics_get_version(void);
const kinematics_link_lengths_t kinematics_get_link_lengths(void);
kinematics_cartesian_position_t kinematics_forward_kinematics(const kinematics_joint_position_t* joint_position);
kinematics_full_results_t kinematics_get_kinematic_results(const kinematics_joint_position_t* joint_position);
""")

C = ffi.dlopen(libpath)

def get_version():
    v = C.kinematics_get_version()
    return {"major": v.major, "minor": v.minor, "patch": v.patch}

def get_link_lengths():
    lengths = C.kinematics_get_link_lengths()
    return {"length_0": lengths.length_0, "length_1": lengths.length_1}

def forward_kinematics(joint_0: float, joint_1: float):
    joint = ffi.new("kinematics_joint_position_t*", {"joint_0": joint_0, "joint_1": joint_1})
    pos = C.kinematics_forward_kinematics(joint)
    return {"x": pos.x, "y": pos.y}

def get_kinematic_results(joint_0: float, joint_1: float):
    joint = ffi.new("kinematics_joint_position_t*", {"joint_0": joint_0, "joint_1": joint_1})
    res = C.kinematics_get_kinematic_results(joint)
    return {
        "x0": res.x0,
        "x1": res.x1,
        "x2": res.x2,
        "y0": res.y0,
        "y1": res.y1,
        "y2": res.y2,
        "xpos": res.xpos,
        "ypos": res.ypos,
    }
