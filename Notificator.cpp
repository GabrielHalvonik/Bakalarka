#include "Notificator.hpp"

Notificator::Notificator() {

}

Notificator::~Notificator() {
    for (Module* temp : this->modules) {
        delete temp;
        temp = nullptr;
    }
}

Notificator* Notificator::getInstance() {
    if (Notificator::instance == nullptr) {
        Notificator::instance = new Notificator;
    }
    return Notificator::instance;
}

void Notificator::registerModule(Module* module) {
    this->modules.push_back(module);
    this->connections.insert({module, QObject::connect(module, &Module::emitting, this, &Notificator::notifyOnEvent)});
}

void Notificator::unregisterModule(Module* module) {
    if (this->connections.count(module)) {
        QObject::disconnect(this->connections[module]);
    }
}

void Notificator::notifyOnEvent(Actions action) {
    for (Module* module : this->modules) {
        module->actionOnModuleEmitting(action);
    }
    emit notificatorRegisteredEmit(action);
}
