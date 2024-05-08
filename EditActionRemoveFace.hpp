#pragma once

#include "EditActionStrategy.hpp"
#include <Qt3DRender/QObjectPicker>
#include <Qt3DRender/QPickTriangleEvent>

using Qt3DRender::QPickTriangleEvent;
using Qt3DRender::QObjectPicker;

class EditActionRemoveFace : public EditActionStrategy, public QObject {
public:
    EditActionRemoveFace(QEntity*);

    void performAction() override;
    void actionActivation(bool) override;

private:
    QObjectPicker* picker;
    QPickTriangleEvent* triangleEvent;
    QMetaObject::Connection conn;
};

