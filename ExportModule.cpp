#include "ExportModule.hpp"
#include "ExportFormatOBJ.hpp"
#include <Qt3DCore/QEntity>
#include "Model.hpp"
#include <Qt3DRender/QGeometryRenderer>
#include <thread>

using Qt3DRender::QGeometryRenderer;

using Qt3DCore::QEntity;

ExportModule::ExportModule() : Module(), exports({}) {
    this->registerExportFormat<ExportFormatOBJ>("obj");
}

ExportModule::~ExportModule() {
    for (ExportFormat* temp : this->exports) {
        delete temp;
        temp = nullptr;
    }
}

void ExportModule::actionOnModuleEmitting(Actions) {

}

void ExportModule::exportTo(const QString& str) {
    QEntity* model = Model::getInstance()->getModelEntity();
    QGeometryRenderer* renderer = model->componentsOfType<QGeometryRenderer>().first();
    if (renderer == nullptr) {
        return;
    }

    if (QString extension = str.split(".").last(); exports.contains(extension)) {
        exports[extension]->fillExportFormat(renderer->geometry());
    }

    emit Module::emitting(Actions::ExportedAssetAction);
}

