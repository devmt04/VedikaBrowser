// Copyright (C) 2025 Mohit Deoli
// SPDX-License-Identifier: GPL-3.0-only


#ifndef WEBAREALAYOUTWIDGET_H
#define WEBAREALAYOUTWIDGET_H

#include <QWidget>
#include <QStackedWidget>
#include <QVector>
#include <QHBoxLayout>
#include "./WebEngineView/webengineview.h"
#include "./WebAreaLayoutManager/webarealayoutmanager.h"

namespace Ui {
class WebAreaLayoutWidget;
}

class WebAreaLayoutWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WebAreaLayoutWidget(QWidget *parent = nullptr);
    ~WebAreaLayoutWidget();
    void addNewWebView(int index);
    void closeWebView(int index);
    void setCurrentWebView(int index);
    void loadUrl(const QUrl &url);
    void goBack();
    void goForward();
    QUrl currentUrl() const;
    void setLayoutMode(int mode);
    int webviewVectorSize() const;

signals:
    void webViewUrlChanged(const QString &url);
    void webViewTitleChanged(int index, const QString &new_title);
    void webViewFaviconChanged(int index, const QIcon &favicon);
    void backButtonState(bool enabled);
    void forwardButtonState(bool enabled);
    void message(const QString &text);

private:
    // Ui::WebAreaLayoutWidget *ui;
    QHBoxLayout *horizontalLayout;
    WebAreaLayoutManager *layoutManager;
    WebEngineView *currentWebEngineView = nullptr;
    QVector<WebEngineView*> globalWebViewVector;
};

#endif // WEBAREALAYOUTWIDGET_H
