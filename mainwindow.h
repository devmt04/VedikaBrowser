// Copyright (C) 2025 Mohit Deoli
// SPDX-License-Identifier: GPL-3.0-only


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QVBoxLayout>
// #include <QStackedWidget>
// #include <QVector>
#include "./lib/ui/navigationbar/navigationbar.h"
// #include "./lib/ui/WebEngineView/webengineview.h"
// #include "./lib/ui/WebAreaLayoutWidget/WebEngineView/webengineview.h"
#include "./lib/ui/tabbar/tabbar.h"
#include "./lib/ui/WebAreaLayoutWidget/webarealayoutwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onSearchRequested(const QUrl &url);
    void onNewTabAdded(int tabIndex);
    void onTabClosed(int tabIndex);
    void onTabSelected(int tabIndex);
    void onWebAreaLayoutChanged(int layout);

private:
    // Ui::MainWindow *ui;
    int init_tabCount = 0;
    QVBoxLayout *centralLayout;
    // FramelessWindow<MainWindow> *window;
    TabBar *tabBar;
    NavigationBar *navigationBar;
    // QStackedWidget *stackedWebArea;
    WebAreaLayoutWidget *webAreaLayout;
    // WebEngineView *currentWebEngineView = nullptr; // or make it a QPointer

    // QVector<WebEngineView*> webEngineViewVector;
};
#endif // MAINWINDOW_H
