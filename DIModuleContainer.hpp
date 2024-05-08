#pragma once

#include "InjectedInstance.hpp"
#include <map>
#include <iostream>
#include <exception>
#include <string>

class DIModuleContainer {
public:
    ~DIModuleContainer();

    static DIModuleContainer* instance();

    template <typename T>
    void registerModule();

    template <typename T>
    T* getModule();

private:
    DIModuleContainer() = default;
    DIModuleContainer(DIModuleContainer&) = default;

public:
    inline static DIModuleContainer* instanceDI {nullptr};
    std::map<std::string, AbstractInjectedInstance*> module {};
};

template <typename T>
void DIModuleContainer::registerModule() {
    T* localInstance = new T;
    std::string type = std::string(typeid(T).name());
    if (!this->module.count(type))
        this->module.insert({type, new InjectedInstance<T>(localInstance)});
}

template <typename T>
T* DIModuleContainer::getModule() {
    std::string type = std::string(typeid(T).name());
    if (this->module.count(type))
        return static_cast<T*>(this->module[type]->get());
    else
        throw std::logic_error("Could not find type in DI container: " + type);
}
