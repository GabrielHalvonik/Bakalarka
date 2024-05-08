#pragma once

#include <Qt3DCore/QTransform>

enum class TransformOperations {
    None,
    Move,
    Scale,
    Rotate
};

enum class Axis : int {
    None = 0,
    X = 1 << 0,
    Y = 1 << 1,
    Z = 1 << 2,
    XY = X | Y,
    XZ = X | Z,
    YZ = Y | Z,
    XYZ = X | Y | Z
};

inline Axis operator|(const Axis& first, const Axis& second) {
    return Axis(static_cast<int>(first) | static_cast<int>(second));
}

inline Axis operator&(const Axis& first, const Axis& second) {
    return Axis(static_cast<int>(first) & static_cast<int>(second));
}

inline Axis operator-(const Axis& first, const Axis& second) {
    return Axis(static_cast<int>(first) & ~static_cast<int>(second));
}

class Transform {
public:
    Transform(Qt3DCore::QTransform* transform) : transform(transform) {}
    virtual ~Transform() = default;

    virtual void doTransformation(float delta, Axis) = 0;
protected:
    Qt3DCore::QTransform* transform;
};

class Translation : public Transform {
public:
    Translation(Qt3DCore::QTransform* transform);

    virtual void doTransformation(float delta, Axis axis) override;
};

class Scale : public Transform {
public:
    Scale(Qt3DCore::QTransform* transform);

    virtual void doTransformation(float delta, Axis axis) override;
};

class Rotation : public Transform {
public:
    Rotation(Qt3DCore::QTransform* transform);

    virtual void doTransformation(float delta, Axis axis) override;
};
