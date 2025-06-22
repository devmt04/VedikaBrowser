// Copyright (C) 2025 Mohit Deoli
// SPDX-License-Identifier: GPL-3.0-only


#ifndef WEBAREALAYOUTWIDGET_H
#define WEBAREALAYOUTWIDGET_H

#include <QWidget>
#include <QStackedWidget>
#include <QVector>
#include <QHBoxLayout>

#include "./WebEngineView/webengineview.h"

namespace Ui {
class WebAreaLayoutWidget;
}

enum class LayoutMode {
    Single = 0,
    Split,
    Grid,
    Popup
};

class WebAreaLayoutWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WebAreaLayoutWidget(QWidget *parent = nullptr);
    ~WebAreaLayoutWidget();
    void addNewWebView(int index); // returns tab index
    void closeWebView(int index);
    void setCurrentWebView(int index);
    void loadUrl(const QUrl &url);
    void goBack();
    void goForward();
    // WebEngineView* currentWebView() const;
    QUrl currentUrl() const;
    void setLayoutMode(LayoutMode mode); // enum { Single, Split, Grid, Popup }
    int webviewVectorSize() const;

signals:
    void webViewUrlChanged(const QString &url);
    void webViewTitleChanged(int index, const QString &new_title);
    void webViewFaviconChanged(int index, const QIcon &favicon);
    void backButtonState(bool enabled);
    void forwardButtonState(bool enabled);

private:
    // Ui::WebAreaLayoutWidget *ui;
    QHBoxLayout *horizontalLayout;
    QStackedWidget *stackedWebArea;
    WebEngineView *currentWebEngineView = nullptr;
    QVector<WebEngineView*> webEngineViewVector;
};

#endif // WEBAREALAYOUTWIDGET_H
