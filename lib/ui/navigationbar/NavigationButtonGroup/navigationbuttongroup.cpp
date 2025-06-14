#include "navigationbuttongroup.h"
#include "ui_navigationbuttongroup.h"

NavigationButtonGroup::NavigationButtonGroup(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::NavigationButtonGroup)
{
    // ui->setupUi(this);
    horizontalLayout = new QHBoxLayout(this);
    backButton = new QPushButton(this);
    forwardButton = new QPushButton(this);
    reloadButton = new QPushButton(this);

    backButton->setProperty("class", "borderless");
    forwardButton->setProperty("class", "borderless");
    reloadButton->setProperty("class", "borderless");

    backButton->setIcon(QIcon(":/lib/resources/icon/arrow_back_black.svg"));
    forwardButton->setIcon(QIcon(":/lib/resources/icon/arrow_forward_black.svg"));
    reloadButton->setIcon(QIcon(":/lib/resources/icon/reload_black.svg"));

    horizontalLayout->addWidget(backButton);
    horizontalLayout->addWidget(forwardButton);
    horizontalLayout->addWidget(reloadButton);
}

NavigationButtonGroup::~NavigationButtonGroup()
{
    delete ui;
}
