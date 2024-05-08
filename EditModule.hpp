#pragma once

#include "Module.hpp"
#include <Qt3DCore/QEntity>
#include <Qt3DCore/QTransform>
#include "EditActionStrategy.hpp"
#include "TransformOperations.hpp"

using Qt3DCore::QEntity;

class EditModule : public Module {
public:
    EditModule();
    virtual ~EditModule();

    void actionOnModuleEmitting(Actions) override;

    void addOrSubAxis(const Axis, bool);
    void selectTransformOperation(const TransformOperations);

    void doTransformation(float);

    TransformOperations getTransformOperationSelected() const;
    Axis getAxis() const;

    template<typename T>
    void registerEditOperation(const QString&);

    void doMeshEditAction(const QString&);

    QMap<QString, EditActionStrategy*> getEditMeshActions() const;

private:
    QEntity* model;

    Qt3DCore::QTransform* transform;
    Transform* transformOperation;
    TransformOperations transformOperationSelected;
    Axis axis {Axis::None};
    QMap<QString, EditActionStrategy*> editMeshCommands;
};

template<typename T>
inline void EditModule::registerEditOperation(const QString& name) {
    if (std::is_base_of<EditActionStrategy, T>::value) {
        this->editMeshCommands.insert(name, new T(this->model));
    }
}
