#pragma once

namespace wb {
    struct CartesianPosition {
        CartesianPosition(float xi, float yi) : x(xi), y(yi) {}
        float x;
        float y;
    };

    struct Transformation {
        Transformation() : a(1), b(0), c(0), d(1) {}
        Transformation(float ai, float bi, float ci, float di) : a(ai), b(bi), c(ci), d(di) {}
        float a;
        float b;
        float c;
        float d;
    };
}