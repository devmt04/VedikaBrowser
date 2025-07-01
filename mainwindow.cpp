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
        └── webAreaLayout (WebAreaLayoutWidget)
            └── WebAreaLayoutManager
                 └── multiple WebEngineView
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
    webAreaLayout = new WebAreaLayoutWidget(centralWidget);

    centralLayout->setContentsMargins(0,0,0,0);
    centralLayout->setSpacing(0);

    centralLayout->addWidget(tabBar);
    centralLayout->addWidget(navigationBar);
    centralLayout->addWidget(webAreaLayout);

    connect(tabBar, &TabBar::newTabAdded, this, &MainWindow::onNewTabAdded);
    connect(tabBar, &TabBar::tabClosed, this, &MainWindow::onTabClosed);
    connect(tabBar, &TabBar::tabSelected, this, &MainWindow::onTabSelected);

    connect(navigationBar, &NavigationBar::searchRequested, this, &MainWindow::onSearchRequested);
    connect(navigationBar, &NavigationBar::pageBack, this, [this](){
        webAreaLayout->goBack();
    });
    connect(navigationBar, &NavigationBar::pageForward, this, [this](){
        webAreaLayout->goForward();
    });
    connect(navigationBar, &NavigationBar::pageReload, this, [this](){
        webAreaLayout->goBack();
    });
    connect(navigationBar, &NavigationBar::layoutChanged, this, &MainWindow::onWebAreaLayoutChanged);

    connect(webAreaLayout, &WebAreaLayoutWidget::webViewUrlChanged, navigationBar, &NavigationBar::setSearchbarText);
    connect(webAreaLayout, &WebAreaLayoutWidget::webViewTitleChanged, this, [this](int index, const QString &new_title){
        tabBar->setTabTitle(index, new_title);
    });
    connect(webAreaLayout, &WebAreaLayoutWidget::webViewFaviconChanged, this, [this](int index, const QIcon &favicon){
        tabBar->setTabFavicon(index, favicon.pixmap(12,12));
    });
    connect(webAreaLayout, &WebAreaLayoutWidget::backButtonState, this, [this](bool enabled){
        navigationBar->setBackButtonState(enabled);
    });
    connect(webAreaLayout, &WebAreaLayoutWidget::forwardButtonState, this, [this](bool enabled){
        navigationBar->setForwardButtonState(enabled);
    });

    connect(webAreaLayout, &WebAreaLayoutWidget::message, this, [this](const QString &text){
        navigationBar->setMessage(text);
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
    webAreaLayout->loadUrl(url);
}

void MainWindow::onNewTabAdded(int tabIndex){
    webAreaLayout->addNewWebView(tabIndex);
}

void MainWindow::onTabSelected(int tabIndex){
    if(tabIndex >= 0){
        webAreaLayout->setCurrentWebView(tabIndex);
        navigationBar->setSearchbarText(webAreaLayout->currentUrl().toDisplayString());
        tabBar->setCurrentTab(tabIndex);
    }else{
        qDebug() << "select tab : tab out of index!";
    }
}

void MainWindow::onTabClosed(int tabIndex){
    if(tabIndex >= 0){
        webAreaLayout->closeWebView(tabIndex);
        if(webAreaLayout->webviewVectorSize() == 0){
            tabBar->addNewTab();
            // TODO : CLOSE APPLICATION INSTEAD
            qDebug() << "new tab added when none left";
        }
        onTabSelected((tabIndex-1)>=0?(tabIndex-1):0);
    }else{
        qDebug() << "Delete tab: tab out of index!";
    }
}


void MainWindow::onWebAreaLayoutChanged(int layout){
    // 0 = single view, 1 = split view, 2 = grid view, 3 = popup view
    // LayoutMode mode = static_cast<LayoutMode>(layout);
    webAreaLayout->setLayoutMode(layout);
}


// TODO : remove .ui file listing from CMake
    // Custom theming
