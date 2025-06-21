// Copyright (C) 2025 Mohit Deoli
// SPDX-License-Identifier: GPL-3.0-only


#include "mainwindow.h"

#include <QApplication>
// #include "./lib/utils/3rd-party/Qt-FramelessWindow/include/FramelessWindow.hpp"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile styleFile(":/lib/resources/styles/main.qss");
    if (styleFile.open(QFile::ReadOnly)) {
        QString style = QLatin1String(styleFile.readAll());
        a.setStyleSheet(style);
        styleFile.close();
    }

    MainWindow w;
    w.show();
    // FramelessWindow<MainWindow> *frameLessWindow = new FramelessWindow<MainWindow>(true);
    // frameLessWindow->setContentsMargins(1,1,1,1);
    // frameLessWindow->show();
    return a.exec();
}
