#pragma once

#include "CartesianPosition.h"
#include <memory>

namespace wb {
    class Joint  {
    public:
        Joint(float init_anglet);

        void setAngle(float angle);
        float getAngle() const;

        Transformation getTransformation() const;

    private:
        float angle_;
    };

    using JointPtr = std::shared_ptr<Joint>;
}
