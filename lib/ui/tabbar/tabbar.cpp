#include "tabbar.h"
#include "ui_tabbar.h"

TabBar::TabBar(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TabBar)
{

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
    topHBoxLayout->setContentsMargins(0,0,0,0);
    this->setLayout(topHBoxLayout);

    // In topHBoxLayout
    customTabBarWidget = new QWidget(this);
    tabHBoxLayout = new QHBoxLayout(customTabBarWidget);
    tabHBoxLayout->setContentsMargins(0,0,0,0);
    // tabHBoxLayout->setSizeConstraint(QLayout::SetMinimumSize);
    customTabBarWidget->setLayout(tabHBoxLayout);
    customTabBarWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed); // Important



    applicationExitButton = new QPushButton(QIcon(":/lib/resources/icon/cross_black.svg"),  "",  this);
    applicationExitButton->setObjectName("applicationExitButton");
    applicationExitButton->setProperty("class", "borderless");
    applicationExitButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    connect(applicationExitButton, &QPushButton::clicked, this, [=]() {
        if (QMessageBox::question(this, "Exit", "Are you sure you want to quit?") == QMessageBox::Yes) {
            qApp->quit();
        }
    });
    // -- end --


    // In customTabBarWidget - tabHBoxLayout
    tabScrollArea = new QScrollArea(customTabBarWidget);
    // tabScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    tabScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    tabScrollArea->setWidgetResizable(true);
    tabScrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed); // Don't expand horizontally
    tabScrollArea->setFixedHeight(40);

    addNewTabButton = new QPushButton(QIcon(":/lib/resources/icon/add_black.svg"), "", customTabBarWidget);
    addNewTabButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    connect(addNewTabButton, &QPushButton::clicked, this, &TabBar::addNewTab);
    // -- end --


    // In tabScrollArea
    tabContainer = new QWidget();
    tabContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed); // Important
    tabContainer->setMaximumHeight(40);

    tabContainerHBoxLayout = new QHBoxLayout(tabContainer);
    tabContainerHBoxLayout->setContentsMargins(0,0,0,0);
    tabContainerHBoxLayout->setSpacing(3);  // or small spacing like 4
    tabContainerHBoxLayout->setAlignment(Qt::AlignLeft);
    tabContainer->setLayout(tabContainerHBoxLayout);
    // -- end --


    // In tabContainer - tabContainerHBoxLayout
    defaultTabItem = new TabItem(tabContainer);
    connect(defaultTabItem, &TabItem::tabClosed, this, &TabBar::closeTab);
    connect(defaultTabItem, &TabItem::tabClicked, this, &TabBar::selectTab);
    tabContainerHBoxLayout->addWidget(defaultTabItem);
    // -- end --


    tabHBoxLayout->addWidget(tabScrollArea);
    tabHBoxLayout->addWidget(addNewTabButton);

    tabScrollArea->setWidget(tabContainer);

    topHBoxLayout->addWidget(customTabBarWidget);
    topHBoxLayout->addWidget(applicationExitButton);

    tabVector.clear();
}

TabBar::~TabBar()
{
    delete ui;
}

void TabBar::addNewTab(){
    TabItem *tab = new TabItem(tabContainer);
    connect(tab, &TabItem::tabClosed, this, &TabBar::closeTab);
    connect(tab, &TabItem::tabClicked, this, &TabBar::selectTab);
    tabContainerHBoxLayout->addWidget(tab);
    tabVector.append(tab);
    emit newTabAdded(tab);
}

void TabBar::closeTab(TabItem *tab){
    tabContainerHBoxLayout->removeWidget(tab);
    tabVector.removeOne(tab);
    tab->deleteLater();
    emit tabClosed(tab);
}

void TabBar::selectTab(TabItem *tab){
    emit tabSelected(tab);
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

