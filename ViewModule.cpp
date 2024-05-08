#include "Effects/QtEffect.hpp"
#include "Effects/QtEffectTexture.hpp"
#include "ViewModule.hpp"

#include <Qt3DCore>
#include <Qt3DRender>
#include <Qt3DInput>
#include <Qt3DExtras>
#include <QtGui/QKeyEvent>
#include "Model.hpp"
#include "Effects/QtEffectMetalRough.cpp"
#include "Effects/QtEffectGooch.hpp"
#include "Effects/QtEffectPhong.hpp"
#include "Effects/QtEffectMorphPhong.hpp"
#include "Effects/QtEffectPerVertex.hpp"
#include "Effects/OwnFlashEffect.hpp"

using Qt3DRender::QGeometryRenderer;

ViewModule::ViewModule() : Module(), controller(new QOrbitCameraController(Model::getInstance()->getRootEntity())) {
    this->effects.insert({"Gooch", new QtEffectGooch});
//    this->effects.insert({"MetalRough", new QtEffectMetalRough});
    this->effects.insert({"Morph", new QtEffectMorphPhong});
    this->effects.insert({"Phong", new QtEffectPhong});
    this->effects.insert({"Texture", new QtEffectTexture});
    this->effects.insert({"Flash", new OwnFlashEffect});

    this->controller->setAcceleration(16.f);
}

ViewModule::~ViewModule() {
    for (auto& [name, effect] : this->effects) {
        delete effect;
        effect = nullptr;
    }
}

void ViewModule::actionOnModuleEmitting(Actions act) {
    switch (act) {
    case Actions::ImportedAssetAction:
        if (this->controller->camera() != nullptr) {
            this->controller->camera()->viewAll();
        }
        Model::getInstance()->getModelEntity()->addComponent(this->effects["Flash"]->getComponent());
        break;

    default: break;
    }
}

QOrbitCameraController* ViewModule::getController() const {
    return this->controller;
}

std::map<std::string, Effect*> ViewModule::getEffects() const {
    return this->effects;
}

void ViewModule::setViewMode(const Qt3DRender::QGeometryRenderer::PrimitiveType type) {
    if (Model::getInstance()->getModelEntity() != nullptr) {
        if (QVector<QGeometryRenderer*> meshes = Model::getInstance()->getModelEntity()->componentsOfType<QGeometryRenderer>(); !meshes.empty()) {
            meshes.first()->setPrimitiveType(type);
        }
    }
}


