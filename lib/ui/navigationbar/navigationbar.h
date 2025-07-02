// Copyright (C) 2025 Mohit Deoli
// SPDX-License-Identifier: GPL-3.0-only


#ifndef NAVIGATIONBAR_H
#define NAVIGATIONBAR_H

#include <QWidget>
#include <QHBoxLayout>
#include <QDebug>
#include <QSizePolicy>
#include <QTimer>

#include "./searchbar/searchbar.h"
#include "./NavigationButtonGroup/navigationbuttongroup.h"
#include "./WebAreaLayoutController/webarealayoutcontroller.h"


namespace Ui {
class NavigationBar;
}

class NavigationBar : public QWidget
{
    Q_OBJECT

public:
    explicit NavigationBar(QWidget *parent = nullptr);
    ~NavigationBar();
    void setSearchbarText(const QString &text);
    void setMessage(const QString &text);
    void setBackButtonState(bool active);
    void setForwardButtonState(bool active);
    void setLayoutControllerIndex(int index);


signals:
    void searchRequested(const QUrl &url);
    void pageBack();
    void pageForward();
    void pageReload();
    void layoutChanged(int layout);

// public slots:
//     void setSearchbarText(const QString &text);

private slots:
    void onSearchBarInFocus();
    void onSearchBarOutFocus();
    void onLineEditReturnPress(const QUrl &url);

private:
    Ui::NavigationBar *ui;
    QHBoxLayout *horizontalLayout;
    NavigationButtonGroup *naviButtonGrp;
    SearchBar *searchBar;
    WebAreaLayoutController *webareaLayoutController;
};

#endif // NAVIGATIONBAR_H
