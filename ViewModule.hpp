#pragma once

#include "Module.hpp"
#include <Qt3DExtras/QFirstPersonCameraController>
#include <Qt3DExtras/QOrbitCameraController>
#include "Effects/Effect.hpp"
#include <Qt3DRender/QGeometryRenderer>

using Qt3DExtras::QFirstPersonCameraController;
using Qt3DExtras::QOrbitCameraController;

class ViewModule : public Module {
public:
    ViewModule();
    virtual ~ViewModule();

    virtual void actionOnModuleEmitting(Actions) override;

    QOrbitCameraController* getController() const;

    std::map<std::string, Effect*> getEffects() const;

    void setViewMode(const Qt3DRender::QGeometryRenderer::PrimitiveType);

private:
    QOrbitCameraController* controller;
    std::map<std::string, Effect*> effects;
};

