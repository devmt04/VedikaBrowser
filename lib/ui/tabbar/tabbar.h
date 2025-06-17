#ifndef TABBAR_H
#define TABBAR_H

#include <QWidget>
#include <QTabBar>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSizePolicy>
#include <QMessageBox>
#include <QScrollArea>
#include "./tabitem/tabitem.h"

#include <QVector>

namespace Ui {
class TabBar;
}

class TabBar : public QWidget
{
    Q_OBJECT

public:
    explicit TabBar(QWidget *parent = nullptr);
    ~TabBar();

// protected:
//     void mouseDoubleClickEvent(QMouseEvent *event) override;

private slots:
    void addNewTab();
    void closeTab(TabItem *tab);

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
