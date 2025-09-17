#include <math.h>
#include <wabo/kinematics.h>
#include "version.h"
#include "Link.h"
#include "Joint.h"
#include <stdio.h>


namespace {
    float link_length_1 = 0.5f;  // Length of the second
    float link_length_0 = sqrt(2*link_length_1*link_length_1);  // Length of the first link


    wb::JointPtr baseJoint{std::make_shared<wb::Joint>(0.0f)};
    wb::JointPtr secondJoint{std::make_shared<wb::Joint>(0.0f)};

    wb::InterfacePtr baseLink{std::make_shared<wb::Link>(link_length_0, baseJoint, nullptr)};
    wb::InterfacePtr secondLink{std::make_shared<wb::Link>(link_length_1, secondJoint, baseLink)};
}

const kinematics_version_t kinematics_get_version(void) {
    return WB_KINEMATICS_VERSION;
}

const kinematics_link_lengths_t kinematics_get_link_lengths(void) {
    kinematics_link_lengths_t lengths;
    lengths.length_0 = link_length_0;
    lengths.length_1 = link_length_1;
    return lengths;
}

kinematics_cartesian_position_t kinematics_forward_kinematics(const kinematics_joint_position_t* joint_position) {
    kinematics_cartesian_position_t position;

    baseJoint->setAngle(joint_position->joint_0);
    secondJoint->setAngle(joint_position->joint_1);
    auto cartesian_pos = secondLink->getOutputPosition();
    position.x = cartesian_pos.x;
    position.y = cartesian_pos.y;

    return position;
}

kinematics_full_results_t kinematics_get_kinematic_results(const kinematics_joint_position_t* joint_position) {
    kinematics_full_results_t result;

    result.x0 = 0.0f;
    result.y0 = 0.0f;

    float L0 = link_length_0;
    float L1 = link_length_1;

    float theta0 = joint_position->joint_0;
    float theta1 = joint_position->joint_1;

    result.x1 = cos(theta0) * L0;
    result.y1 = sin(theta0) * L0;

    result.x2 = result.x1 + cos(theta0 + theta1) * L1;
    result.y2 = result.y1 + sin(theta0 + theta1) * L1;

    result.xpos = result.x2;
    result.ypos = result.y2;

    return result;
}