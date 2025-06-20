// Copyright (C) 2025 Mohit Deoli
// SPDX-License-Identifier: GPL-3.0-only


#ifndef WEBENGINEVIEW_H
#define WEBENGINEVIEW_H

#include <QWidget>
#include <QHBoxLayout>
#include <QtWebEngineWidgets/QWebEngineView>
#include <QWebEngineHistory>

namespace Ui {
class WebEngineView;
}

class WebEngineView : public QWidget
{
    Q_OBJECT

public:
    explicit WebEngineView(QWidget *parent = nullptr);
    ~WebEngineView();
    void loadUrl(const QUrl &url);
    QUrl getUrl() const;
    void back();
    void forward();
    void reload();
    // void checkHistoryNavigationState();

signals:
    void urlChanged(const QString &url, WebEngineView *senderView);
    void titleChanged(const QString &new_title);
    void faviconChanged(const QIcon &new_favicon);
    void backButtonState(bool state);
    void forwardButtonState(bool state);

private slots:
    void onUrlChanged(const QUrl &url);
    void onTitleChanged(const QString &title);
    void onFaviconChanged(const QIcon &new_favicon);

private:
    // Ui::WebEngineView *ui;
    QHBoxLayout *layout;
    QWebEngineView *webEngineView;
};

#endif // WEBENGINEVIEW_H
