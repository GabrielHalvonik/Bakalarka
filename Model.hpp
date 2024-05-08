#pragma once

#include <Qt3DCore/QEntity>

using Qt3DCore::QEntity;

class Model {
public:
    ~Model();

    static Model* getInstance();

    QEntity* getRootEntity() const;

    void addModel(QEntity*);

    QEntity* getModelEntity() const;

private:
    Model();

private:
    inline static Model* instance;
    QEntity* rootEntity;
    QEntity* modelEntity;
};

