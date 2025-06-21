#ifndef TABBAR_H
#define TABBAR_H

// Copyright (C) 2025 Mohit Deoli
// SPDX-License-Identifier: GPL-3.0-only


#include <QWidget>
#include <QTabBar>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSizePolicy>
#include <QMessageBox>
#include <QScrollArea>
#include <QScrollBar>
#include "./tabitem/tabitem.h"

#include <QVector>
#include <QEvent>
#include <QWheelEvent>

namespace Ui {
class TabBar;
}

class TabBar : public QWidget
{
    Q_OBJECT

public:
    explicit TabBar(QWidget *parent = nullptr);
    ~TabBar();
    void setTabTitle(int index, const QString &title);
    void setTabFavicon(int index, const QPixmap &pixmap);
    void setCurrentTab(int index);

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

    // void mouseDoubleClickEvent(QMouseEvent *event) override;


signals:
    void newTabAdded(int tabIndex);
    void tabClosed(int tabIndex);
    void tabSelected(int tabIndex);

public slots:
    void addNewTab();

private slots:
    void closeTab(TabItem *tab);
    void selectTab(TabItem *tab);

private:
    Ui::TabBar *ui;
    QHBoxLayout *topHBoxLayout;
    QWidget *customTabBarWidget;
    QHBoxLayout *tabHBoxLayout;
    QScrollArea *tabScrollArea;
    QWidget *tabContainer;
    QHBoxLayout *tabContainerHBoxLayout;
    TabItem *defaultTabItem;
    TabItem *defaultTabItem2;
    QPushButton *addNewTabButton;
    QPushButton *applicationExitButton;

    QVector<TabItem*> tabVector;
};

#endif // TABBAR_H
