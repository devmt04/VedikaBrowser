#include "mainwindow.h"
#include "./ui_mainwindow.h"

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

    this->setCentralWidget(centralWidget);
    this->showMaximized();
}

MainWindow::~MainWindow()
{

    delete ui;
}
