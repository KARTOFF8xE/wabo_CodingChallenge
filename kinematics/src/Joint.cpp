#include "Joint.h"
#include <cmath>

namespace wb {
  Joint::Joint(float init_angle) : angle_(init_angle){}

  void Joint::setAngle(float angle) {
    angle_ = angle;
  }

  float Joint::getAngle() const {
    return angle_;
  }

  Transformation Joint::getTransformation() const {
    return Transformation{float(std::cos(angle_)), -float(std::sin(angle_)), float(std::sin(angle_)), float(std::cos(angle_))};
  }
}