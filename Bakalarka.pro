QT += 3dcore 3drender 3dinput 3dextras

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Application.cpp \
    DIModuleContainer.cpp \
    EditActionRemoveFace.cpp \
    EditActionStrategy.cpp \
    EditModule.cpp \
    Effects/CustomEffect.cpp \
    ExportFormat.cpp \
    ExportFormatOBJ.cpp \
    ExportModule.cpp \
    ImportFormat.cpp \
    ImportFormatOBJ.cpp \
    ImportModule.cpp \
    InjectedInstance.cpp \
    Model.cpp \
    Module.cpp \
    Notificator.cpp \
    Effects/Effect.cpp \
    Effects/OwnFlashEffect.cpp \
    Effects/QtEffect.cpp \
    Effects/QtEffectGooch.cpp \
    Effects/QtEffectMetalRough.cpp \
    Effects/QtEffectMorphPhong.cpp \
    Effects/QtEffectPerVertex.cpp \
    Effects/QtEffectPhong.cpp \
    Effects/QtEffectTexture.cpp \
    TransformOperations.cpp \
    UI/EditModuleUI.cpp \
    UI/ExportModuleUI.cpp \
    UI/ImportModuleUI.cpp \
    UI/MainUI.cpp \
    UI/ModuleUI.cpp \
    UI/PropertyWidgets/Matrix3Widget.cpp \
    UI/PropertyWidgets/Vector2DWidget.cpp \
    UI/ViewModuleUI.cpp \
    UI/EffectWidget.cpp \
    ViewModule.cpp \
    main.cpp

HEADERS += \
    AbstractInjectedInstance.hpp \
    Actions.hpp \
    Application.hpp \
    DIModuleContainer.hpp \
    EditActionRemoveFace.hpp \
    EditActionStrategy.hpp \
    EditModule.hpp \
    Effects/CustomEffect.hpp \
    ExportFormat.hpp \
    ExportFormatOBJ.hpp \
    ExportModule.hpp \
    ImportFormat.hpp \
    ImportFormatOBJ.hpp \
    ImportModule.hpp \
    InjectedInstance.hpp \
    Model.hpp \
    Module.hpp \
    Notificator.hpp \
    Effects/Effect.hpp \
    Effects/OwnFlashEffect.hpp \
    Effects/QtEffect.hpp \
    Effects/QtEffectGooch.hpp \
    Effects/QtEffectMetalRough.hpp \
    Effects/QtEffectMorphPhong.hpp \
    Effects/QtEffectPerVertex.hpp \
    Effects/QtEffectPhong.hpp \
    Effects/QtEffectTexture.hpp \
    TransformOperations.hpp \
    UI/EditModuleUI.hpp \
    UI/ExportModuleUI.hpp \
    UI/ImportModuleUI.hpp \
    UI/MainUI.hpp \
    UI/ModuleUI.hpp \
    UI/PropertyWidgets/Matrix3Widget.hpp \
    UI/PropertyWidgets/Vector2DWidget.hpp \
    UI/ViewModuleUI.hpp \
    UI/EffectWidget.hpp \
    ViewModule.hpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    assets.qrc
