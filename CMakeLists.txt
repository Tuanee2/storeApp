cmake_minimum_required(VERSION 3.16)

project(storeApp VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.5)


qt_add_executable(appstoreApp
    main.cpp
)

qt_add_qml_module(appstoreApp
    URI storeApp
    VERSION 1.0
    QML_FILES
        Main.qml
        QML_FILES view/SideBar.qml
        RESOURCES resource.qrc
        SOURCES configManager/colorconfigmanager.h configManager/colorconfigmanager.cpp
        SOURCES configManager/sizeconfigmanager.h configManager/sizeconfigmanager.cpp
        SOURCES core/command.h core/command.cpp
        SOURCES core/customercore.h core/customercore.cpp
        SOURCES core/batchcore.h core/batchcore.cpp
        SOURCES core/productcore.h core/productcore.cpp
        SOURCES core/ordercore.h core/ordercore.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appstoreApp PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appstoreApp
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appstoreApp
    PRIVATE Qt6::Quick
)

include(GNUInstallDirs)
install(TARGETS appstoreApp
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
