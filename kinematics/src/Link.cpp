#include "Link.h"
#include <assert.h>
#include <cmath>

namespace wb {
    Link::Link(float len, JointPtr joint, InterfacePtr parent) : length_(len), joint_(joint), parent_(parent) {
        assert(joint_ != nullptr); // Joint must not be null
    }

    float Link::getLength() const {
        return length_;
    }

    CartesianPosition Link::getOutputPosition() const {
        CartesianPosition parent_pos(0.0f, 0.0f);
        auto angle = joint_->getAngle();
        Transformation transformation;
        if (parent_) {
            transformation = parent_->getTransformation();
        }

        float x_local = length_ * std::cos(angle);
        float y_local = length_ * std::sin(angle);

        float x = transformation.a * x_local + transformation.b * y_local;
        float y = transformation.c * x_local + transformation.d * y_local;

        if (parent_) {
            parent_pos = parent_->getOutputPosition();
        }

        x = parent_pos.x + x;
        y = parent_pos.y + y;

        return CartesianPosition(x, y);
    }

    Transformation Link::getTransformation() const {
        return joint_->getTransformation();
    }
}
