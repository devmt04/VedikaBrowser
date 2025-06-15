#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    // ui->setupUi(this);
    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* centralLayout = new QVBoxLayout(centralWidget);

    navigationBar = new NavigationBar(centralWidget);
    webEngineView = new WebEngineView(centralWidget);

    centralLayout->setContentsMargins(0,0,0,0);
    centralLayout->setSpacing(0);

    centralLayout->addWidget(navigationBar);
    centralLayout->addWidget(webEngineView);

    connect(navigationBar, &NavigationBar::searchRequested, this, &MainWindow::onSearchRequested);
    connect(webEngineView, &WebEngineView::urlChanged, navigationBar, &NavigationBar::setSearchbarText);

    this->setCentralWidget(centralWidget);
    this->showMaximized();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::onSearchRequested(const QUrl &url){
    qDebug() << url ;
    webEngineView->loadUrl(url);
}

