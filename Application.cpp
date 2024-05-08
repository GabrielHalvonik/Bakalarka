#include "Application.hpp"
#include "ViewModule.hpp"
#include "ImportModule.hpp"
#include "EditModule.hpp"
#include "ExportModule.hpp"

Application::Application() : QObject(), notificator(Notificator::getInstance()) {
    Application::addModule<ViewModule>();
    Application::addModule<ImportModule>();
    Application::addModule<ExportModule>();
    Application::addModule<EditModule>();
}

Application::~Application() {
    if (Application::instance) {
        delete Application::instance;
        Application::instance = nullptr;
    }
}

Application* Application::getInstance() {
    if (Application::instance == nullptr) {
        Application::instance = new Application;
    }
    return instance;
}
