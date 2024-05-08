#pragma once

#include <QObject>
#include "Actions.hpp"

class Module : public QObject {
    Q_OBJECT
public:
    Module() = default;
    virtual ~Module() = default;

    virtual void actionOnModuleEmitting(Actions) = 0;

signals:
    void emitting(Actions);
};
