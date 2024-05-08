#include "EditActionRemoveFace.hpp"
#include <Qt3DRender/QPickEvent>
#include <Qt3DRender/QAttribute>
#include <Qt3DRender/QMesh>
#include <Qt3DRender/QBuffer>

using Qt3DRender::QPickEvent;
using Qt3DRender::QAttribute;
using Qt3DRender::QMesh;
using Qt3DRender::QBuffer;

EditActionRemoveFace::EditActionRemoveFace(Qt3DCore::QEntity* model) : EditActionStrategy(model), picker(new QObjectPicker), triangleEvent(nullptr) {
    EditActionStrategy::model->addComponent(this->picker);

    QMetaObject::Connection conn = QObject::connect(this->picker, &QObjectPicker::clicked, this, [this](QPickEvent* event) -> void {
        this->triangleEvent = dynamic_cast<QPickTriangleEvent*>(event);
        performAction();
    });

//    this->actionActivation(false);
}

void EditActionRemoveFace::performAction() {
    if (triangleEvent != nullptr) {
        QAttribute* indexAttr = triangleEvent->entity()->componentsOfType<QMesh>().first()->geometry()->attributes().last();
        indexAttr->buffer()->setData(indexAttr->buffer()->data().remove(triangleEvent->triangleIndex() * 3 * sizeof(unsigned short), 3 * sizeof(unsigned short)));
        indexAttr->setCount(indexAttr->count() - 3);
    }
}

void EditActionRemoveFace::actionActivation(bool checked) {
    if (checked) {
        this->picker->setEnabled(true);
    } else {
        this->picker->setEnabled(false);
    }
}
