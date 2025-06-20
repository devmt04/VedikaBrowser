#include "tabbar.h"
#include "ui_tabbar.h"

TabBar::TabBar(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TabBar)
{
    // TODO : Remove tabVector

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

    tabVector.clear();

    // ui->setupUi(this);
    this->setStyleSheet("QWidget{background-color:#FFE5BF;border:none;}");

    topHBoxLayout = new QHBoxLayout(this);
    topHBoxLayout->setContentsMargins(0,0,0,0);
    // topHBoxLayout->setAlignment(Qt::AlignBottom);
    this->setLayout(topHBoxLayout);

    // In topHBoxLayout
    customTabBarWidget = new QWidget(this);
    tabHBoxLayout = new QHBoxLayout(customTabBarWidget);
    // tabHBoxLayout->setAlignment(Qt::AlignBottom);
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
    tabScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    tabScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    tabScrollArea->setWidgetResizable(true);
    tabScrollArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed); // Don't expand horizontally
    tabScrollArea->setFixedHeight(40);
    // tabScrollArea->setAlignment(Qt::AlignBottom);

    addNewTabButton = new QPushButton(QIcon(":/lib/resources/icon/add_black.svg"), "", customTabBarWidget);
    addNewTabButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    connect(addNewTabButton, &QPushButton::clicked, this, &TabBar::addNewTab);
    // -- end --


    // In tabScrollArea
    tabContainer = new QWidget();
    tabContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed); // Important
    // tabContainer->setMaximumHeight(40);
    tabContainer->setFixedHeight(40);

    tabContainerHBoxLayout = new QHBoxLayout(tabContainer);
    tabContainerHBoxLayout->setContentsMargins(0,0,0,0);
    tabContainerHBoxLayout->setSpacing(3);
    tabContainerHBoxLayout->setAlignment(Qt::AlignBottom);
    tabContainer->setLayout(tabContainerHBoxLayout);
    // -- end --

    tabHBoxLayout->addWidget(tabScrollArea);
    tabHBoxLayout->addWidget(addNewTabButton);

    tabScrollArea->setWidget(tabContainer);

    topHBoxLayout->addWidget(customTabBarWidget);
    topHBoxLayout->addWidget(applicationExitButton);
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
    int index = tabVector.indexOf(tab);
    emit newTabAdded(index);
    emit tabSelected(index);
}

void TabBar::closeTab(TabItem *tab){
    int index = tabVector.indexOf(tab);
    if (index == -1) return;

    tabVector.removeAt(index);
    tabContainerHBoxLayout->removeWidget(tab);
    tab->deleteLater();

    emit tabClosed(index);
}

void TabBar::selectTab(TabItem *tab){
    int index = tabVector.indexOf(tab);
    if (index >= 0) {
        emit tabSelected(index);
    }
}

void TabBar::setTabTitle(int index, const QString &title) {
    if (index >= 0) {
        tabVector[index]->setTitle(title);
    }
}

void TabBar::setTabFavicon(int index, const QPixmap &pixmap){
    if (index >= 0) {
        tabVector[index]->setFavicon(pixmap);
    }
}

void TabBar::setCurrentTab(int index){
    for (int i = 0; i < tabVector.size(); ++i) {
        tabVector[i]->setSelected(i == index);
    }
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

