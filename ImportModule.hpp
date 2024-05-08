#pragma once

#include "ImportFormat.hpp"
#include "Module.hpp"
#include <Qt3DCore/QEntity>
#include <Qt3DRender/QMesh>
#include <Qt3DExtras/QGoochMaterial>
#include "Model.hpp"

class ImportModule : public Module {
public:
    ImportModule();
    virtual ~ImportModule();

    void actionOnModuleEmitting(Actions) override;
    void import(const QString&);

    template <typename T>
    void registerImportFormat(const QString&);

private:
    QMap<QString, ImportFormat*> imports;
};

template<typename T>
inline void ImportModule::registerImportFormat(const QString& format) {
    if (std::is_base_of<ImportFormat, T>::value) {
        imports.insert(format, new T);
    }
}
