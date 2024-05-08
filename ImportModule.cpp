#include "ImportModule.hpp"
#include <ImportFormatOBJ.hpp>

ImportModule::ImportModule() : Module(), imports({}) {
//    this->registerImportFormat<ImportFormatOBJ>("obj");
}

ImportModule::~ImportModule() {
    for (ImportFormat* temp : this->imports) {
        delete temp;
        temp = nullptr;
    }
}

void ImportModule::actionOnModuleEmitting(Actions) {

}

void ImportModule::import(const QString& str) {
    QEntity* model = Model::getInstance()->getModelEntity();

    if (QString extension = str.split(".").last(); imports.contains(extension)) {
        imports[extension]->loadFile(str.toStdString());
        imports[extension]->addGeometryToModel(model);
    } else {
        Qt3DRender::QMesh* mesh = new Qt3DRender::QMesh(model);
        mesh->setSource(QUrl::fromLocalFile(str));
        model->addComponent(mesh);
    }

    emit ImportModule::emitting(Actions::ImportedAssetAction);
}
