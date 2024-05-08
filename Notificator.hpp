#pragma once

#include "Module.hpp"
#include "Actions.hpp"
#include <vector>
#include <map>

class Notificator : public QObject {
    Q_OBJECT
public:
    ~Notificator();

    static Notificator* getInstance();

    void registerModule(Module*);
    void unregisterModule(Module*);

signals:
    void notificatorRegisteredEmit(Actions);

private slots:
    void notifyOnEvent(Actions);

private:
    Notificator();

private:
    inline static Notificator* instance;

    std::vector<Module*> modules {};
    std::map<Module*, QMetaObject::Connection> connections {};
};
