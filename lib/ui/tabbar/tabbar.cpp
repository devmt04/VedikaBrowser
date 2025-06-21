// Copyright (C) 2025 Mohit Deoli
// SPDX-License-Identifier: GPL-3.0-only


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
    // this->setObjectName("tabbar");
    this->setStyleSheet("QWidget{background-color:#FFE5BF;border:none;}");
    // this->setStyleSheet("QWidget#tabbar{padding-right:12px;}");

    topHBoxLayout = new QHBoxLayout(this);
    topHBoxLayout->setSpacing(0);
    topHBoxLayout->setContentsMargins(0,0,0,0);
    // topHBoxLayout->setAlignment(Qt::AlignBottom);
    this->setLayout(topHBoxLayout);

    // In topHBoxLayout
    customTabBarWidget = new QWidget(this);
    tabHBoxLayout = new QHBoxLayout(customTabBarWidget);
    // tabHBoxLayout->setAlignment(Qt::AlignBottom);
    tabHBoxLayout->setContentsMargins(0,0,10,0); // left, top, right, bottom
    // tabHBoxLayout->setSizeConstraint(QLayout::SetMinimumSize);
    customTabBarWidget->setLayout(tabHBoxLayout);
    customTabBarWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed); // Important


    applicationExitButton = new QPushButton(QIcon(":/lib/resources/icon/cross_black.svg"),  "",  this);
    applicationExitButton->setObjectName("applicationExitButton");
    applicationExitButton->setProperty("class", "borderless");
    applicationExitButton->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
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

    tabScrollArea->viewport()->installEventFilter(this);

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

bool TabBar::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == tabScrollArea->viewport() && event->type() == QEvent::Wheel) {
        QWheelEvent *wheelEvent = static_cast<QWheelEvent *>(event);

        // Support both vertical wheel (like mouse) and horizontal delta (like trackpad)
        int scrollDelta = wheelEvent->angleDelta().y();
        if (scrollDelta == 0) {
            scrollDelta = wheelEvent->angleDelta().x();
        }

        if (scrollDelta != 0) {
            QScrollBar *hScroll = tabScrollArea->horizontalScrollBar();
            int step = 30;
            hScroll->setValue(hScroll->value() - (scrollDelta > 0 ? step : -step));
            return true;
        }
    }

    return QWidget::eventFilter(watched, event);
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

