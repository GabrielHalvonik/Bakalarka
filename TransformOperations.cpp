#include "TransformOperations.hpp"


Translation::Translation(Qt3DCore::QTransform* transform) : Transform(transform) {}

void Translation::doTransformation(float delta, Axis axis) {
    QVector3D original = Transform::transform->translation();

    if ((axis & Axis::X) == Axis::X) {
        original.setX(original.x() + delta);
        Transform::transform->setTranslation(original);
    }
    if ((axis & Axis::Y) == Axis::Y) {
        original.setY(original.y() + delta);
        Transform::transform->setTranslation(original);
    }
    if ((axis & Axis::Z) == Axis::Z) {
        original.setZ(original.z() + delta);
        Transform::transform->setTranslation(original);
    }
}

Scale::Scale(Qt3DCore::QTransform* transform) : Transform(transform) {}

void Scale::doTransformation(float delta, Axis axis) {
    QVector3D original = Transform::transform->scale3D();

    if ((axis & Axis::X) == Axis::X) {
        original.setX(original.x() + delta);
        Transform::transform->setScale3D(original);
    }
    if ((axis & Axis::Y) == Axis::Y) {
        original.setY(original.y() + delta);
        Transform::transform->setScale3D(original);
    }
    if ((axis & Axis::Z) == Axis::Z) {
        original.setZ(original.z() + delta);
        Transform::transform->setScale3D(original);
    }
}

Rotation::Rotation(Qt3DCore::QTransform* transform) : Transform(transform) {}

void Rotation::doTransformation(float delta, Axis axis) {
    QQuaternion original = Transform::transform->rotation();

    if ((axis & Axis::X) == Axis::X) {
        original.setX(original.x() + delta);
        original.normalize();
    }
    if ((axis & Axis::Y) == Axis::Y) {
        original.setY(original.y() + delta);
        original.normalize();
    }
    if ((axis & Axis::Z) == Axis::Z) {
        original.setZ(original.z() + delta);
        original.normalize();
    }
    Transform::transform->setRotation(original);
}
