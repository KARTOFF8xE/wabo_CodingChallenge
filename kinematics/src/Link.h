#pragma once

#include "Interface.h"
#include "Joint.h"

namespace wb {
    class Link : public Interface {
    public:
        Link(float len, JointPtr joint, InterfacePtr parent);

        float getLength() const;

        CartesianPosition getOutputPosition() const override;

        Transformation getTransformation() const override;

    private:
        float length_;
        JointPtr joint_;
        InterfacePtr parent_;
    };

    using LinkPtr = std::shared_ptr<Link>;
}