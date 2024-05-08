#pragma once

class AbstractInjectedInstance {
public:
    AbstractInjectedInstance(void* ptr) : ptr(ptr) { }

    virtual ~AbstractInjectedInstance() = default;

    inline void* get() { return ptr; }

private:
    void* ptr {};
};
