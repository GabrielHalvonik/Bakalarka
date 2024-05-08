#include "Application.hpp"
#include <QApplication>

#include "UI/MainUI.hpp"
#include "UI/ViewModuleUI.hpp"
#include "UI/ImportModuleUI.hpp"
#include "UI/EditModuleUI.hpp"
#include "UI/ExportModuleUI.hpp"


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    MainUI mainUI;
    mainUI.registerModule<ViewModuleUI>();
    mainUI.registerModule<EditModuleUI>();
    mainUI.registerModule<ImportModuleUI>();
    mainUI.registerModule<ExportModuleUI>();
    mainUI.show();

    return a.exec();
}
