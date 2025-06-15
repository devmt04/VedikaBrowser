#ifndef TABBAR_H
#define TABBAR_H

#include <QWidget>
#include <QTabBar>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSizePolicy>
#include <QMessageBox>

namespace Ui {
class TabBar;
}

class TabBar : public QWidget
{
    Q_OBJECT

public:
    explicit TabBar(QWidget *parent = nullptr);
    ~TabBar();

private:
    Ui::TabBar *ui;
    QHBoxLayout *horizontalLayout;
    QPushButton *applicationExitButton;
    QTabBar *tabBar;
};

#endif // TABBAR_H
