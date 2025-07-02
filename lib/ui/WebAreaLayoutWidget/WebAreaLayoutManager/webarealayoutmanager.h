// Copyright (C) 2025 Mohit Deoli
// SPDX-License-Identifier: GPL-3.0-only

#ifndef WEBAREALAYOUTMANAGER_H
#define WEBAREALAYOUTMANAGER_H

#include <QWidget>
#include <QVector>
#include <QHBoxLayout>
#include <QSplitter>
#include <QGridLayout>
#include <QSizePolicy>
#include <QDebug>
#include <QDialog>

#include "../WebEngineView/webengineview.h"
#include "./TabSelectionDialog/tabselectiondialog.h"

// namespace Ui {
// class WebAreaLayoutManager;
// }

class WebAreaLayoutManager : public QWidget
{
    Q_OBJECT

public:
    // explicit WebAreaLayoutManager(QWidget *parent = nullptr/*, QVector<WebEngineView*> *_globalViewVector = nullptr*/);
    explicit WebAreaLayoutManager(QWidget *parent, const QVector<WebEngineView*> &_globalViewVector);
    ~WebAreaLayoutManager();
    enum LayoutMode {
        Single = 0,
        Split,
        Grid
        // Popup can be handled externally (e.g. floating windows)
    };

    void applyLayout(int mode);
    void applyLayout(int mode, const QVector<WebEngineView*>& views);
    void setCurrentWebArea(WebEngineView *view);
    void deleteWebView(WebEngineView *view);
    void addWebView(WebEngineView *view);

signals:
    void message(const QString &text, int mode); // messages will be displayed at NavigationBar

private:
    // Ui::WebAreaLayoutManager *ui;
    int currentActiveLayout = 0; // So the defualt startup tab will ve opened in SignleView
    const QVector<WebEngineView*> &globalViewVector;
    QVector<WebEngineView*> currentActiveViews;
    WebEngineView *currentSelectedView;

    QHBoxLayout *horizontalLayout = nullptr;
    QSplitter *splitterLayout = nullptr;
    QGridLayout *gridLayout = nullptr;
    QWidget *gridContainer = nullptr;

    TabSelectionDialog *tabSelectionDialog;
    void clearLayout(bool free = false); // Remove all children safely
    void setupSingle(const QVector<WebEngineView*> &views);
    void setupSplit(const QVector<WebEngineView*> &views);
    void setupGrid(const QVector<WebEngineView*> &views);
    // popup

};

#endif // WEBAREALAYOUTMANAGER_H
