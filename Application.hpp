#pragma once

#include <QMainWindow>

#include "DIModuleContainer.hpp"
#include "Module.hpp"
#include "Notificator.hpp"

class Application : public QObject {
    Q_OBJECT
public:
    static Application* getInstance();

    template <typename T>
    void addModule();


private:
    Application();
    ~Application();

private:
    inline static Application* instance;
    Notificator* notificator;
};


template <typename T>
void Application::addModule() {
    if (std::is_base_of<Module, T>::value) {
        DIModuleContainer::instance()->registerModule<T>();
        this->notificator->registerModule(DIModuleContainer::instance()->getModule<T>());
    }
    else {
        throw std::logic_error("Not base class of Module in Application::addModule.");
    }
}
