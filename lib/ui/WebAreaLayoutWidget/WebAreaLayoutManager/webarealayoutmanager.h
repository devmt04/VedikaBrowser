// Copyright (C) 2025 Mohit Deoli
// SPDX-License-Identifier: GPL-3.0-only

#ifndef WEBAREALAYOUTMANAGER_H
#define WEBAREALAYOUTMANAGER_H

#include <QWidget>
#include <QVector>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QDebug>
#include "../WebEngineView/webengineview.h"

// namespace Ui {
// class WebAreaLayoutManager;
// }

class WebAreaLayoutManager : public QWidget
{
    Q_OBJECT

public:
    explicit WebAreaLayoutManager(QWidget *parent = nullptr);
    ~WebAreaLayoutManager();
    enum LayoutMode {
        Single = 0,
        Split,
        Grid
        // Popup can be handled externally (e.g. floating windows)
    };

    void applyLayout(int mode, const QVector<WebEngineView*>& views); // or use enum instead of int
    void setCurrentWebArea(WebEngineView *view);
    void deleteWebView(WebEngineView *view);
    void addWebView(WebEngineView *view);

private:
    // Ui::WebAreaLayoutManager *ui;
    int currentActiveLayout = 0; // So the defualt startup tab will ve opened in SignleView
    QVector<WebEngineView*> currentActiveViews;
    WebEngineView *currentSelectedView;
    void clearLayout(bool free = false); // Remove all children safely
    void setupSingle(const QVector<WebEngineView*>& views);
    void setupSplit(const QVector<WebEngineView*>& views);
    void setupGrid(const QVector<WebEngineView*>& views);
    // popup

};

#endif // WEBAREALAYOUTMANAGER_H
