#pragma once

#include "CartesianPosition.h"
#include <memory>

namespace wb {
  class Interface {
  public:

    virtual CartesianPosition getOutputPosition() const = 0;

    virtual Transformation getTransformation() const = 0;
  };

  using InterfacePtr = std::shared_ptr<Interface>;
}
