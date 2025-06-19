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

    defaultWebEngineView = new WebEngineView(stackedWebArea);
    currentWebEngineView = defaultWebEngineView;

    stackedWebArea->addWidget(defaultWebEngineView);
    stackedWebArea->setCurrentWidget(defaultWebEngineView);

    centralLayout->setContentsMargins(0,0,0,0);
    centralLayout->setSpacing(0);

    centralLayout->addWidget(tabBar);
    centralLayout->addWidget(navigationBar);
    centralLayout->addWidget(stackedWebArea);

    connect(tabBar, &TabBar::newTabAdded, this, &MainWindow::onNewTabAdded);
    connect(tabBar, &TabBar::tabClosed, this, &MainWindow::onTabClosed);
    connect(tabBar, &TabBar::tabSelected, this, &MainWindow::onTabSelected);
    connect(navigationBar, &NavigationBar::searchRequested, this, &MainWindow::onSearchRequested);
    connect(defaultWebEngineView, &WebEngineView::urlChanged, navigationBar, &NavigationBar::setSearchbarText);

    this->setCentralWidget(centralWidget);
    this->showMaximized();
    // this->setWindowFlags(Qt::FramelessWindowHint);
    // TODO : Make window frameless and add ability to make it move, resize from corners
    // setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint);

    // TODO : MANAGE DEFUALT TABITEM DELETE
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

    // TabSession session;
    // session.tabItem = tab;
    // session.webEngineView = newWebWidget;
    // tabSessions.append(session);
    // tabSessions.insert(tabIndex, TabSession{tabBar->getTabItem(index), webWidget});
    webEngineViewVector.insert(tabIndex, newWebWidget);

    connect(newWebWidget, &WebEngineView::urlChanged, navigationBar, &NavigationBar::setSearchbarText);
    currentWebEngineView = newWebWidget;
    navigationBar->setSearchbarText("");

    connect(newWebWidget, &WebEngineView::titleChanged, this, [=](const QString &new_title){
        // tab->setTitle(new_title);
        tabBar->setTabTitle(tabIndex, new_title);
    });
}

void MainWindow::onTabSelected(int tabIndex){
    if(tabIndex >= 0){
        WebEngineView *view = webEngineViewVector.at(tabIndex);
        stackedWebArea->setCurrentWidget(view);
        currentWebEngineView = view;
        navigationBar->setSearchbarText(view->getUrl().toDisplayString());
    }else{
        qDebug() << "select tab : tab out of index!";
    }

    // for(const TabSession &session : tabSessions){
    //     if(session.tabItem == tab){
    //         stackedWebArea->setCurrentWidget(session.webEngineView);
    //         currentWebEngineView = session.webEngineView;
    //         navigationBar->setSearchbarText(session.webEngineView->getUrl().toDisplayString());
    //         break;
    //     }
    // }
    // can be optimize this later with a helper method or std::ranges.
}

void MainWindow::onTabClosed(int tabIndex){
    if(tabIndex >= 0){
        WebEngineView *view = webEngineViewVector.takeAt(tabIndex);
        stackedWebArea->removeWidget(view);
        view->deleteLater();
    }else{
        qDebug() << "Delete tab: tab out of index!";
    }

    // for (int i = 0; i < tabSessions.size(); ++i) {
    //     if (tabSessions[i].tabItem == tab) {
    //         WebEngineView *view = tabSessions[i].webEngineView;

    //         stackedWebArea->removeWidget(view);
    //         view->deleteLater();

    //         tabSessions.removeAt(i);
    //         break;
    //     }
    // }
    // TODO : Impliment a helper class for webEngineView look ups
}
