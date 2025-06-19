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
            └── webEngineView (WebEngineView)
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

    // TODO : MANAGE DEFUALT TABITEM DELETE, SELECT EVENT
}

MainWindow::~MainWindow()
{
    // delete ui;
}


void MainWindow::onSearchRequested(const QUrl &url){
    qDebug() << url ;
    currentWebEngineView->loadUrl(url);
}

void MainWindow::onNewTabAdded(TabItem *tab){
    WebEngineView *webWidget = new WebEngineView(stackedWebArea);
    stackedWebArea->addWidget(webWidget);
    stackedWebArea->setCurrentWidget(webWidget);

    tabMap.insert(tab, webWidget);

    connect(webWidget, &WebEngineView::urlChanged, navigationBar, &NavigationBar::setSearchbarText);
    currentWebEngineView = webWidget;
    navigationBar->setSearchbarText("");

    connect(webWidget, &WebEngineView::titleChanged, this, [=](const QString &new_title){
        tab->setTitle(new_title);
    });
}

void MainWindow::onTabSelected(TabItem *tab){
    WebEngineView *view = tabMap.value(tab);
    if(view){
        stackedWebArea->setCurrentWidget(view);
        currentWebEngineView = view;
        navigationBar->setSearchbarText(view->getUrl().toDisplayString());
    }
}

void MainWindow::onTabClosed(TabItem *tab){
    WebEngineView *view = tabMap.take(tab); // .take() will also remove the tab
    if(view){
        stackedWebArea->removeWidget(view);
        view->deleteLater();
    }
    // TODO : HANDLE currentWebEngineView, handle navbar url
}


