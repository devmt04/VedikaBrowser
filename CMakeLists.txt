cmake_minimum_required(VERSION 3.16)

project(VedikaWebBrowser VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets WebEngineWidgets)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(VedikaWebBrowser
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        lib/ui/navigationbar/searchbar/searchbar.h lib/ui/navigationbar/searchbar/searchbar.cpp lib/ui/navigationbar/searchbar/searchbar.ui
        AppQRC.qrc
        lib/ui/WebAreaLayoutWidget/WebEngineView/webengineview.h lib/ui/WebAreaLayoutWidget/WebEngineView/webengineview.cpp     
        lib/ui/navigationbar/navigationbar.h lib/ui/navigationbar/navigationbar.cpp lib/ui/navigationbar/navigationbar.ui
        lib/ui/navigationbar/NavigationButtonGroup/navigationbuttongroup.h lib/ui/navigationbar/NavigationButtonGroup/navigationbuttongroup.cpp lib/ui/navigationbar/NavigationButtonGroup/navigationbuttongroup.ui
        lib/ui/tabbar/tabbar.h lib/ui/tabbar/tabbar.cpp lib/ui/tabbar/tabbar.ui
        lib/ui/tabbar/tabitem/tabitem.h lib/ui/tabbar/tabitem/tabitem.cpp lib/ui/tabbar/tabitem/tabitem.ui
        lib/ui/navigationbar/WebAreaLayoutController/webarealayoutcontroller.h lib/ui/navigationbar/WebAreaLayoutController/webarealayoutcontroller.cpp lib/ui/navigationbar/WebAreaLayoutController/webarealayoutcontroller.ui
        lib/ui/WebAreaLayoutWidget/webarealayoutwidget.h lib/ui/WebAreaLayoutWidget/webarealayoutwidget.cpp lib/ui/WebAreaLayoutWidget/webarealayoutwidget.ui
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET VedikaWebBrowser APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(VedikaWebBrowser SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(VedikaWebBrowser
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(VedikaWebBrowser PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::WebEngineWidgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.VedikaWebBrowser)
endif()
set_target_properties(VedikaWebBrowser PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS VedikaWebBrowser
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(VedikaWebBrowser)
endif()
