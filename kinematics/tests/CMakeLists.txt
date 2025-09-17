enable_testing()
include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.14.0
)
# For MSVC: prevent overriding parent project’s runtime settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Do not install gtest/gmock when we install our project
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
set(INSTALL_GMOCK OFF CACHE BOOL "" FORCE)
# Optionally avoid building gmock if not needed
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)
include(GoogleTest)


add_executable(kinematic_test kinematic_test.cpp)
target_link_libraries(kinematic_test PRIVATE wb_kinematics_static GTest::gtest_main)
gtest_discover_tests(kinematic_test)
