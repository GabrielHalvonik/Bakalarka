#pragma once

#include "Module.hpp"
#include "ExportFormat.hpp"
#include <QMap>

class ExportModule : public Module {
public:
    ExportModule();
    virtual ~ExportModule();

    void actionOnModuleEmitting(Actions) override;

    template <typename T>
    void registerExportFormat(const QString&);

    void exportTo(const QString&);

private:
    QMap<QString, ExportFormat*> exports;
};


template<typename T>
inline void ExportModule::registerExportFormat(const QString& format) {
    if (std::is_base_of<ExportFormat, T>::value) {
        exports.insert(format, new T);
    }
}
