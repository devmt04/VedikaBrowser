#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // this->setWindowFlags(Qt::Popup);
    // this->setWindowFlags(Qt::Window | Qt::CustomizeWindowHint);
    // ui->setupUi(this);
    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* centralLayout = new QVBoxLayout(centralWidget);
    centralWidget->setLayout(centralLayout);

    tabBar = new TabBar(centralWidget);
    // tabBar = new FramelessWindow<TabBar>(false, centralWidget);
    navigationBar = new NavigationBar(centralWidget);
    webEngineView = new WebEngineView(centralWidget);

    centralLayout->setContentsMargins(0,0,0,0);
    centralLayout->setSpacing(0);

    centralLayout->addWidget(tabBar);
    centralLayout->addWidget(navigationBar);
    centralLayout->addWidget(webEngineView);

    connect(navigationBar, &NavigationBar::searchRequested, this, &MainWindow::onSearchRequested);
    connect(webEngineView, &WebEngineView::urlChanged, navigationBar, &NavigationBar::setSearchbarText);

    this->setCentralWidget(centralWidget);
    // this->setWindowFlags(Qt::FramelessWindowHint);
    // TODO : Make window frameless and add ability to make it move, resize from corners
    this->showMaximized();
    // setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::onSearchRequested(const QUrl &url){
    qDebug() << url ;
    webEngineView->loadUrl(url);
}

