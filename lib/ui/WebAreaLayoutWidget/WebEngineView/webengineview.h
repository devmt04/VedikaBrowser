// Copyright (C) 2025 Mohit Deoli
// SPDX-License-Identifier: GPL-3.0-only


#ifndef WEBENGINEVIEW_H
#define WEBENGINEVIEW_H

#include <QWidget>
#include <QHBoxLayout>
#include <QtWebEngineWidgets/QWebEngineView>
#include <QWebEngineHistory>
#include <QDebug>

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
    QString getTitle() const;
    // getfavivon
    void back();
    void forward();
    void reload();
    // void checkHistoryNavigationState();

signals:
    void urlChanged(const QString &url);
    void titleChanged(const QString &new_title);
    void faviconChanged(const QIcon &new_favicon);
    void backButtonState(bool enabled);
    void forwardButtonState(bool enabled);

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
