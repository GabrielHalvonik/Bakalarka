#include "DIModuleContainer.hpp"

DIModuleContainer::~DIModuleContainer() {
    if (DIModuleContainer::instanceDI) {
        delete DIModuleContainer::instanceDI;
        DIModuleContainer::instanceDI = nullptr;
    }

    for (auto& [name, instance] : this->module) {
        delete instance;
        instance = nullptr;
    }
}

DIModuleContainer* DIModuleContainer::instance() {
    if (DIModuleContainer::instanceDI == nullptr) {
        DIModuleContainer::instanceDI = new DIModuleContainer();
    }
    return DIModuleContainer::instanceDI;
}
