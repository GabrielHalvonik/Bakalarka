#pragma once

#include <memory>
#include "AbstractInjectedInstance.hpp"

template <typename T>
class InjectedInstance : public AbstractInjectedInstance {
public:
    InjectedInstance(T*);
    virtual ~InjectedInstance() = default;
private:
    T* instancePtr {};
};

template<typename T>
InjectedInstance<T>::InjectedInstance(T* ptr) : AbstractInjectedInstance(ptr), instancePtr(ptr) {

}
