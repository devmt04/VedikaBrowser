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

    this->setCentralWidget(centralWidget);
    this->showMaximized();

    // default tab
    tabBar->addNewTab();


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
    qDebug() << tabIndex;
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

    currentWebEngineView = newWebWidget;
    navigationBar->setSearchbarText("");
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
}

void MainWindow::onTabClosed(int tabIndex){
    if(tabIndex >= 0){
        WebEngineView *view = webEngineViewVector.takeAt(tabIndex);
        stackedWebArea->removeWidget(view);
        view->deleteLater();
        if(webEngineViewVector.size() == 0){
            tabBar->addNewTab();
            // TODO : CLOSE APPLICATION INSTEAD
            qDebug() << "new tab added when none left";
        }
    }else{
        qDebug() << "Delete tab: tab out of index!";
    }
}
