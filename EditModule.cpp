#include "EditModule.hpp"
#include "Model.hpp"
#include "EditActionRemoveFace.hpp"

EditModule::EditModule() : transform(new Qt3DCore::QTransform()), transformOperation(nullptr), editMeshCommands({}) {
    this->model = Model::getInstance()->getModelEntity();
    this->model->addComponent(this->transform);

    this->registerEditOperation<EditActionRemoveFace>("RemoveFace");
}

EditModule::~EditModule() {
    for (EditActionStrategy* temp : this->editMeshCommands) {
        delete temp;
        temp = nullptr;
    }

    delete transform;
    transform = nullptr;
}

void EditModule::actionOnModuleEmitting(Actions) {

}

void EditModule::addOrSubAxis(const Axis axe, bool add) {
    if (add) {
        this->axis = this->axis | axe;
    } else {
        this->axis = this->axis - axe;
    }

    if (this->axis != Axis::None) {
        emit emitting(Actions::MeshBeginTranslateAction);
    } else {
        emit emitting(Actions::MeshEndTranslateAction);
    }
}

void EditModule::selectTransformOperation(const TransformOperations operation) {
    this->transformOperationSelected = operation;

    if (this->transformOperation != nullptr) {
        delete this->transformOperation;
    }
    switch (operation) {
        case TransformOperations::None:
            this->transformOperation = nullptr;
            break;
        case TransformOperations::Move:
            this->transformOperation = new Translation(this->transform);
            break;
        case TransformOperations::Scale:
            this->transformOperation = new Scale(this->transform);
            break;
        case TransformOperations::Rotate:
            this->transformOperation = new Rotation(this->transform);
            break;
    }
}

void EditModule::doTransformation(float delta) {
    if (this->transformOperationSelected != TransformOperations::None && this->transformOperation != nullptr) {
        this->transformOperation->doTransformation(delta, this->axis);
    }
}

TransformOperations EditModule::getTransformOperationSelected() const {
    return this->transformOperationSelected;
}

Axis EditModule::getAxis() const {
    return this->axis;
}

void EditModule::doMeshEditAction(const QString& actionName) {
    if (this->editMeshCommands.contains(actionName)) {
        EditActionStrategy* action = this->editMeshCommands[actionName];
        action->performAction();
    }
}

QMap<QString, EditActionStrategy*> EditModule::getEditMeshActions() const {
    return this->editMeshCommands;
}
