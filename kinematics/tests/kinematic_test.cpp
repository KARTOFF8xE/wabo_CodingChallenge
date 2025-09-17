#include <gtest/gtest.h>
#include <version.h>
#include <wabo/kinematics.h>
#include <cmath>

namespace {
    float PI = 3.14159265f;
}

TEST(KinematicsTest, Get_Version) {
    kinematics_version_t version = kinematics_get_version();
    EXPECT_EQ(version.major, WB_KINEMATICS_VERSION.major);
    EXPECT_EQ(version.minor, WB_KINEMATICS_VERSION.minor);
    EXPECT_EQ(version.patch, WB_KINEMATICS_VERSION.patch);
}

TEST(KinematicsTest, Link_Lengths) {
    kinematics_link_lengths_t lengths = kinematics_get_link_lengths();
    EXPECT_GT(lengths.length_0, 0.0f);
    EXPECT_GT(lengths.length_1, 0.0f);

    EXPECT_NEAR(std::sqrt(lengths.length_1 * lengths.length_1 + lengths.length_1 * lengths.length_1), lengths.length_0, 0.0001f);
}

TEST(KinematicsTest, Forward_Kinematics) {
    kinematics_joint_position_t joint_position;
    joint_position.joint_0 = 0.0f;
    joint_position.joint_1 = 0.0f;

    kinematics_cartesian_position_t position = kinematics_forward_kinematics(&joint_position);
    kinematics_link_lengths_t lengths = kinematics_get_link_lengths();


    EXPECT_NEAR(position.x, lengths.length_0 + lengths.length_1, 0.0001f);
    EXPECT_NEAR(position.y, 0.0f, 0.0001f);


    joint_position.joint_0 = PI / 2.0f;
    joint_position.joint_1 = 0.0f;

    position = kinematics_forward_kinematics(&joint_position);


    EXPECT_NEAR(position.x, 0.0f, 0.0001f);
    EXPECT_NEAR(position.y, lengths.length_0 + lengths.length_1, 0.0001f);


    joint_position.joint_0 = PI / 2.0f;
    joint_position.joint_1 = -PI / 2.0f;
    position = kinematics_forward_kinematics(&joint_position);

    EXPECT_NEAR(position.x, lengths.length_1, 0.0001f);
    EXPECT_NEAR(position.y, lengths.length_0, 0.0001f);
}

TEST(KinematicsTest, StretchedArm) {
    kinematics_joint_position_t joints{0.0f, 0.0f};
    kinematics_link_lengths_t lengths = kinematics_get_link_lengths();
    kinematics_full_results_t res = kinematics_get_kinematic_results(&joints);

    EXPECT_FLOAT_EQ(res.x0, 0.0f);
    EXPECT_FLOAT_EQ(res.y0, 0.0f);
    EXPECT_NEAR(res.x1, lengths.length_0, 1e-5);
    EXPECT_NEAR(res.y1, 0.0f, 1e-5);
    EXPECT_NEAR(res.x2, lengths.length_0 + lengths.length_1, 1e-5);
    EXPECT_NEAR(res.y2, 0.0f, 1e-5);
    EXPECT_NEAR(res.xpos, res.x2, 1e-5);
    EXPECT_NEAR(res.ypos, res.y2, 1e-5);
}

TEST(KinematicsTest, UpwardsArm) {
    kinematics_joint_position_t joints{static_cast<float>(M_PI/2), 0.0f};
    kinematics_link_lengths_t lengths = kinematics_get_link_lengths();
    kinematics_full_results_t res = kinematics_get_kinematic_results(&joints);

    EXPECT_NEAR(res.x1, 0.0f, 1e-5);
    EXPECT_NEAR(res.y1, lengths.length_0, 1e-5);
    EXPECT_NEAR(res.x2, 0.0f, 1e-5);
    EXPECT_NEAR(res.y2, lengths.length_0 + lengths.length_1, 1e-5);
}

TEST(KinematicsTest, BothJoints45Deg) {
    float angle = static_cast<float>(M_PI/4);
    kinematics_joint_position_t joints{angle, angle};
    kinematics_link_lengths_t lengths = kinematics_get_link_lengths();
    kinematics_full_results_t res = kinematics_get_kinematic_results(&joints);

    float x1 = cos(angle) * lengths.length_0;
    float y1 = sin(angle) * lengths.length_0;
    float x2 = x1 + cos(2*angle) * lengths.length_1;
    float y2 = y1 + sin(2*angle) * lengths.length_1;

    EXPECT_NEAR(res.x1, x1, 1e-5);
    EXPECT_NEAR(res.y1, y1, 1e-5);
    EXPECT_NEAR(res.x2, x2, 1e-5);
    EXPECT_NEAR(res.y2, y2, 1e-5);
}

TEST(KinematicsTest, SecondJointMinus90Deg) {
    kinematics_joint_position_t joints{0.0f, static_cast<float>(-M_PI/2)};
    kinematics_link_lengths_t lengths = kinematics_get_link_lengths();
    kinematics_full_results_t res = kinematics_get_kinematic_results(&joints);

    float x1 = cos(0.0f) * lengths.length_0;
    float y1 = sin(0.0f) * lengths.length_0;
    float x2 = x1 + cos(-M_PI/2) * lengths.length_1;
    float y2 = y1 + sin(-M_PI/2) * lengths.length_1;

    EXPECT_NEAR(res.x1, x1, 1e-5);
    EXPECT_NEAR(res.y1, y1, 1e-5);
    EXPECT_NEAR(res.x2, x2, 1e-5);
    EXPECT_NEAR(res.y2, y2, 1e-5);
}
