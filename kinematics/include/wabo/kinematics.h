#ifndef WB_KINEMATICS_H
#define WB_KINEMATICS_H


#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
   unsigned int major;        // Major version number
    unsigned int minor;        // Minor version number
    unsigned int patch;        // Patch version number
} kinematics_version_t;


const kinematics_version_t kinematics_get_version(void);

typedef struct {
    float length_0;
    float length_1;
} kinematics_link_lengths_t;

const kinematics_link_lengths_t kinematics_get_link_lengths(void);

typedef struct {
    float x;
    float y;
} kinematics_cartesian_position_t;

typedef struct {
    float joint_0;
    float joint_1;
} kinematics_joint_position_t;

kinematics_cartesian_position_t kinematics_forward_kinematics(const kinematics_joint_position_t* joint_position);

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

kinematics_full_results_t kinematics_get_kinematic_results(const kinematics_joint_position_t* joint_position);

#ifdef __cplusplus
}
#endif

#endif /* WB_KINEMATICS_H */
