#include "Model.hpp"

Model::Model() : rootEntity(new QEntity), modelEntity(new QEntity(rootEntity)) {

}

QEntity* Model::getModelEntity() const {
    return this->modelEntity;
}

Model::~Model() {
    if (Model::instance) {
        delete Model::instance;
        Model::instance = nullptr;
    }

    if (this->modelEntity) {
        delete this->modelEntity;
        this->modelEntity = nullptr;
    }

    if (this->rootEntity) {
        delete this->rootEntity;
        this->rootEntity = nullptr;
    }
}

Model* Model::getInstance() {
    if (Model::instance == nullptr) {
        Model::instance = new Model;
    }
    return instance;
}

QEntity* Model::getRootEntity() const {
    return this->rootEntity;
}

void Model::addModel(Qt3DCore::QEntity* entity) {
    entity->setParent(this->rootEntity);
}
