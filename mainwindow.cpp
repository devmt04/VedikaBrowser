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
    // stackedWebArea = new QStackedWidget(centralWidget);
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
        // if(currentWebEngineView!=nullptr){
        //     currentWebEngineView->back();
        // }
    });
    connect(navigationBar, &NavigationBar::pageForward, this, [this](){
        webAreaLayout->goForward();
    });
    connect(navigationBar, &NavigationBar::pageReload, this, [this](){
        webAreaLayout->goBack();
    });
    connect(navigationBar, &NavigationBar::layoutChanged, this, &MainWindow::onWebAreaLayoutChanged);

    connect(webAreaLayout, &WebAreaLayoutWidget::webViewUrlChanged, navigationBar, &NavigationBar::setSearchbarText);
    connect(webAreaLayout, &WebAreaLayoutWidget::webViewTitleChanged, this, [=](int index, const QString &new_title){
        tabBar->setTabTitle(index, new_title);
    });
    connect(webAreaLayout, &WebAreaLayoutWidget::webViewFaviconChanged, this, [=](int index, const QIcon &favicon){
        tabBar->setTabFavicon(index, favicon.pixmap(12,12));
    });
    connect(webAreaLayout, &WebAreaLayoutWidget::backButtonState, this, [=](bool enabled){
        navigationBar->setBackButtonState(enabled);
    });
    connect(webAreaLayout, &WebAreaLayoutWidget::forwardButtonState, this, [=](bool enabled){
        navigationBar->setForwardButtonState(enabled);
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
    // connect(webAreaLayout, &WebAreaLayoutWidget::webViewUrlChanged, navigationBar, &NavigationBar::setSearchbarText);
    // connect(webAreaLayout, &WebAreaLayoutWidget::webViewTitleChanged, this, [=](const QString &new_title){
    //     tabBar->setTabTitle(tabIndex, new_title);
    // });
    // connect(webAreaLayout, &WebAreaLayoutWidget::webViewFaviconChanged, this, [=](const QIcon &favicon){
    //     tabBar->setTabFavicon(tabIndex, favicon.pixmap(12,12));
    // });
    // connect(webAreaLayout, &WebAreaLayoutWidget::backButtonState, this, [=](bool enabled){
    //     navigationBar->setBackButtonState(enabled);
    // });
    // connect(webAreaLayout, &WebAreaLayoutWidget::forwardButtonState, this, [=](bool enabled){
    //     navigationBar->setForwardButtonState(enabled);
    // });
    // WebEngineView *newWebWidget = new WebEngineView(stackedWebArea);
    // stackedWebArea->addWidget(newWebWidget);
    // stackedWebArea->setCurrentWidget(newWebWidget);

    // webEngineViewVector.insert(tabIndex, newWebWidget);

    // connect(newWebWidget, &WebEngineView::urlChanged, navigationBar, &NavigationBar::setSearchbarText);
    // connect(newWebWidget, &WebEngineView::titleChanged, this, [=](const QString &new_title){
    //     tabBar->setTabTitle(tabIndex, new_title);
    // });
    // connect(newWebWidget, &WebEngineView::faviconChanged, this, [=](const QIcon &favicon){
    //     tabBar->setTabFavicon(tabIndex, favicon.pixmap(12,12));
    // });
    // connect(newWebWidget, &WebEngineView::backButtonState, this, [=](bool state){
    //     if(newWebWidget == currentWebEngineView){
    //         navigationBar->setBackButtonState(state);
    //     }
    // });
    // connect(newWebWidget, &WebEngineView::forwardButtonState, this, [=](bool state){
    //     if(newWebWidget == currentWebEngineView){
    //         navigationBar->setForwardButtonState(state);
    //     }
    // });
}

void MainWindow::onTabSelected(int tabIndex){
    qDebug() << "s "<< tabIndex;
    if(tabIndex >= 0){
        // WebEngineView *view = webEngineViewVector.at(tabIndex);
        // stackedWebArea->setCurrentWidget(view);
        // currentWebEngineView = view;
        webAreaLayout->setCurrentWebView(tabIndex);
        navigationBar->setSearchbarText(webAreaLayout->currentUrl().toDisplayString());
        tabBar->setCurrentTab(tabIndex);
    }else{
        qDebug() << "select tab : tab out of index!";
    }
}

void MainWindow::onTabClosed(int tabIndex){
    // qDebug() << tabIndex;
    qDebug() << "c "<< tabIndex;
    if(tabIndex >= 0){
        // WebEngineView *view = webEngineViewVector.takeAt(tabIndex);
        // stackedWebArea->removeWidget(view);
        // view->deleteLater();
        webAreaLayout->closeWebView(tabIndex);
        onTabSelected(tabIndex-1);
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
    LayoutMode mode = static_cast<LayoutMode>(layout);
    webAreaLayout->setLayoutMode(mode);
    // if((layout == 1) && (webEngineViewVector.size() < 2)){
    //     qDebug() << "Split view requires two or more tabs to be opened!";
    //     // TODO : Instead open a default startup page
    // }
    // webEngineViewVector
}


// TODO : remove .ui file listing from CMake
    // Custom theming
