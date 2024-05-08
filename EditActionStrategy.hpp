#pragma once

#include <Qt3DCore/QEntity>

using Qt3DCore::QEntity;

class EditActionStrategy {
public:
    EditActionStrategy(QEntity*);
    virtual ~EditActionStrategy() = default;

    virtual void performAction() = 0;
    virtual void actionActivation(bool) = 0;


protected:
    QEntity* model;
};

