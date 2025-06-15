#include "tabbar.h"
#include "ui_tabbar.h"

TabBar::TabBar(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TabBar)
{
    // ui->setupUi(this);
    horizontalLayout = new QHBoxLayout(this);

    applicationExitButton = new QPushButton(this);
    applicationExitButton->setObjectName("applicationExitButton");
    applicationExitButton->setProperty("class", "borderless");
    applicationExitButton->setIcon(QIcon(":/lib/resources/icon/cross_black.svg"));
    applicationExitButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    connect(applicationExitButton, &QPushButton::clicked, this, [=]() {
        if (QMessageBox::question(this, "Exit", "Are you sure you want to quit?") == QMessageBox::Yes) {
            qApp->quit();
        }
    });

    tabBar = new QTabBar(this);

    tabBar->addTab("HelloWorld");
    tabBar->addTab("HelloWorld2");

    horizontalLayout->addWidget(tabBar);
    horizontalLayout->addWidget(applicationExitButton);
}

TabBar::~TabBar()
{
    delete ui;
}
