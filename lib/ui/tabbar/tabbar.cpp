#include "tabbar.h"
#include "ui_tabbar.h"

TabBar::TabBar(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TabBar)
{

    // TODO : Create Custom TabBar
    // HLayout -> TabBar + ExirButton
        // TabBar -> ScrollArea + AddTabNtm
            // ScrollArea -> customTabs

    //  [<] [Tab1][Tab2][Tab3][+] [>]

    /*
    QHBoxLayout (topHBoxLayout)
    ├── QWidget (customTabBarWidget)
    │   └── QHBoxLayout (tabHBoxLayout)
    │       ├── QPushButton [<] (optional)
    │       ├── QScrollArea (tabScrollArea)
    │       │   └── QWidget (tabContainer)
    │       │       └── QHBoxLayout (tabContainerHBoxLayout)
    │       │           ├── TabItem1
    │       │           └── TabItem2
    │       ├── QPushButton [+]
    │       └── QPushButton [>] (optional)
    └── QPushButton (Exit)
    */

    // ui->setupUi(this);
    this->setStyleSheet("QWidget{background-color:#FFE5BF;}");

    topHBoxLayout = new QHBoxLayout(this);
    this->setLayout(topHBoxLayout);

    customTabBarWidget = new QWidget(this);
    tabHBoxLayout = new QHBoxLayout(customTabBarWidget);
    customTabBarWidget->setLayout(tabHBoxLayout);

    tabScrollArea = new QScrollArea(customTabBarWidget);
    // tabScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    tabScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    tabScrollArea->setWidgetResizable(true); // Important!

    addNewTabButton = new QPushButton(QIcon(":/lib/resources/icon/add_black.svg"), "", customTabBarWidget);

    tabContainer = new QWidget();
    tabContainerHBoxLayout = new QHBoxLayout(tabContainer);
    tabContainer->setLayout(tabContainerHBoxLayout);

    defaultTabItem = new TabItem(tabContainer);
    tabContainerHBoxLayout->addWidget(defaultTabItem);

    tabHBoxLayout->addWidget(tabScrollArea);
    tabHBoxLayout->addWidget(addNewTabButton);

    applicationExitButton = new QPushButton(QIcon(":/lib/resources/icon/cross_black.svg"),  "",  this);
    applicationExitButton->setObjectName("applicationExitButton");
    applicationExitButton->setProperty("class", "borderless");
    applicationExitButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    connect(applicationExitButton, &QPushButton::clicked, this, [=]() {
        if (QMessageBox::question(this, "Exit", "Are you sure you want to quit?") == QMessageBox::Yes) {
            qApp->quit();
        }
    });

    topHBoxLayout->addWidget(customTabBarWidget);
    topHBoxLayout->addWidget(applicationExitButton);

}

TabBar::~TabBar()
{
    delete ui;
}





// void TabBar::mouseDoubleClickEvent(QMouseEvent *event){
//     QWidget *mainWindow = this->window();
//     if(mainWindow->isMaximized()){
//         mainWindow->showNormal();
//     }else{
//         mainWindow->showMaximized();
//     }
//     qDebug() << "Clicked";
//     // TODO : Hanle window drag
// }




/*tabScrollArea->setWidgetResizable(true);
tabScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
tabScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
tabScrollArea->setFrameStyle(QFrame::NoFrame); // Optional: no border
tabScrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
*/


/*
    tabBar = new QTabBar(tabScrollArea);
    tabBar->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
    tabBar->setExpanding(false); // Don't force tab width to expand
    tabBar->setUsesScrollButtons(false); // Disable built-in buttons (optional)

    // tabBar->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    tabBar->addTab("New Tab");

    // tabBar->setExpanding(true);
    // tabBar->setElideMode(Qt::ElideRight); // Truncate tab titles with ...
    // tabBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    addNewTabButton = new QPushButton(tabLayoutWidget);
    addNewTabButton->setIcon(QIcon(":/lib/resources/icon/add_black.svg"));
    // addNewTabButton->setProperty("class", "borderless");

    connect(addNewTabButton, &QPushButton::clicked, this, [=]() {
        tabBar->addTab("New Tab");
    });


    tabLayoutWidget->setStyleSheet("QWidget{background-color:#FFE5BF;}");

    tabScrollArea->setWidget(tabBar);
    tabHBoxLayout->addWidget(tabScrollArea);

    // tabHBoxLayout->addWidget(tabBar);
    tabHBoxLayout->addWidget(addNewTabButton);
    tabHBoxLayout->addStretch();
    tabHBoxLayout->setContentsMargins(10,10,10,0);

    horizontalLayout->setContentsMargins(0,0,0,0);
    horizontalLayout->setSpacing(0);
    // tabLayoutWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    horizontalLayout->addWidget(tabLayoutWidget);
    horizontalLayout->addWidget(applicationExitButton);
    */
