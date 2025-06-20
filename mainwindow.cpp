// Copyright (C) 2025 Mohit Deoli
// SPDX-License-Identifier: GPL-3.0-only


#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    /*, ui(new Ui::MainWindow)*/
{
    /*
MainWindow (QMainWindow)
└── centralWidget (QWidget)
    └── QVBoxLayout (centralLayout)
        ├── tabBar (TabBar)
        ├── navigationBar (NavigationBar)
        └── stackedWebArea (QStackedWidget)
            └── multiple WebEngineView *
*/

    // this->setWindowFlags(Qt::Popup);
    // this->setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
    // ui->setupUi(this);


    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* centralLayout = new QVBoxLayout(centralWidget);
    centralWidget->setLayout(centralLayout);

    tabBar = new TabBar(centralWidget);
    // tabBar = new FramelessWindow<TabBar>(false, centralWidget);
    navigationBar = new NavigationBar(centralWidget);
    stackedWebArea = new QStackedWidget(centralWidget);

    centralLayout->setContentsMargins(0,0,0,0);
    centralLayout->setSpacing(0);

    centralLayout->addWidget(tabBar);
    centralLayout->addWidget(navigationBar);
    centralLayout->addWidget(stackedWebArea);

    connect(tabBar, &TabBar::newTabAdded, this, &MainWindow::onNewTabAdded);
    connect(tabBar, &TabBar::tabClosed, this, &MainWindow::onTabClosed);
    connect(tabBar, &TabBar::tabSelected, this, &MainWindow::onTabSelected);

    connect(navigationBar, &NavigationBar::searchRequested, this, &MainWindow::onSearchRequested);
    connect(navigationBar, &NavigationBar::pageBack, this, [this](){
        if(currentWebEngineView!=nullptr){
            currentWebEngineView->back();
        }
    });
    connect(navigationBar, &NavigationBar::pageForward, this, [this](){
        if(currentWebEngineView!=nullptr){
            currentWebEngineView->forward();
        }
    });
    connect(navigationBar, &NavigationBar::pageReload, this, [this](){
        if(currentWebEngineView!=nullptr){
            currentWebEngineView->reload();
        }
    });

    this->setCentralWidget(centralWidget);
    this->showMaximized();

    // default tab
    tabBar->addNewTab();

    // this->setWindowFlags(Qt::FramelessWindowHint);
    // TODO : Make window frameless and add ability to make it move, resize from corners
    // setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint);
}

MainWindow::~MainWindow()
{
// delete ui;
}


void MainWindow::onSearchRequested(const QUrl &url){
    qDebug() << url ;
    currentWebEngineView->loadUrl(url);
}

void MainWindow::onNewTabAdded(int tabIndex){
    WebEngineView *newWebWidget = new WebEngineView(stackedWebArea);
    stackedWebArea->addWidget(newWebWidget);
    stackedWebArea->setCurrentWidget(newWebWidget);

    webEngineViewVector.insert(tabIndex, newWebWidget);

    connect(newWebWidget, &WebEngineView::urlChanged, navigationBar, &NavigationBar::setSearchbarText);
    connect(newWebWidget, &WebEngineView::titleChanged, this, [=](const QString &new_title){
        tabBar->setTabTitle(tabIndex, new_title);
    });
    connect(newWebWidget, &WebEngineView::faviconChanged, this, [=](const QIcon &favicon){
        tabBar->setTabFavicon(tabIndex, favicon.pixmap(12,12));
    });
    connect(newWebWidget, &WebEngineView::backButtonState, this, [=](bool state){
        if(newWebWidget == currentWebEngineView){
            navigationBar->setBackButtonState(state);
        }
    });
    connect(newWebWidget, &WebEngineView::forwardButtonState, this, [=](bool state){
        if(newWebWidget == currentWebEngineView){
            navigationBar->setForwardButtonState(state);
        }
    });
}

void MainWindow::onTabSelected(int tabIndex){
    if(tabIndex >= 0){
        WebEngineView *view = webEngineViewVector.at(tabIndex);
        stackedWebArea->setCurrentWidget(view);
        currentWebEngineView = view;
        navigationBar->setSearchbarText(view->getUrl().toDisplayString());
        tabBar->setCurrentTab(tabIndex);
    }else{
        qDebug() << "select tab : tab out of index!";
    }
}

void MainWindow::onTabClosed(int tabIndex){
    qDebug() << tabIndex;
    if(tabIndex >= 0){
        WebEngineView *view = webEngineViewVector.takeAt(tabIndex);
        stackedWebArea->removeWidget(view);
        view->deleteLater();
        onTabSelected(tabIndex-1);
        if(webEngineViewVector.size() == 0){
            tabBar->addNewTab();
            // TODO : CLOSE APPLICATION INSTEAD
            qDebug() << "new tab added when none left";
        }
    }else{
        qDebug() << "Delete tab: tab out of index!";
    }
}

// TODO : Enable Scrolling of tabs when overflowed
   // Tab options on right click
