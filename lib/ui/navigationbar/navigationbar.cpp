#include "navigationbar.h"
#include "ui_navigationbar.h"

NavigationBar::NavigationBar(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::NavigationBar)
{
    // ui->setupUi(this);
    horizontalLayout = new QHBoxLayout(this);

    naviBtnGrp = new NavigationButtonGroup(this);
    searchBar = new SearchBar(this);

    horizontalLayout->setContentsMargins(3,5,5,5); // int left, int top, int right, int bottom
    horizontalLayout->addWidget(naviBtnGrp);
    horizontalLayout->addWidget(searchBar);
}

NavigationBar::~NavigationBar()
{
    delete ui;
}
