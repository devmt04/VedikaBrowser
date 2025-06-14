#ifndef NAVIGATIONBAR_H
#define NAVIGATIONBAR_H

#include <QWidget>
#include <QHBoxLayout>

#include "./searchbar/searchbar.h"
#include "./NavigationButtonGroup/navigationbuttongroup.h"

namespace Ui {
class NavigationBar;
}

class NavigationBar : public QWidget
{
    Q_OBJECT

public:
    explicit NavigationBar(QWidget *parent = nullptr);
    ~NavigationBar();

private:
    Ui::NavigationBar *ui;
    QHBoxLayout *horizontalLayout;
    NavigationButtonGroup *naviBtnGrp;
    SearchBar *searchBar;
};

#endif // NAVIGATIONBAR_H
