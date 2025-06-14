#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    // ui->setupUi(this);
    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* centralLayout = new QVBoxLayout(centralWidget);
    centralLayout->setContentsMargins(0,0,0,0);
    centralLayout->setSpacing(0);
    searchBar = new SearchBar(centralWidget);
    centralLayout->addWidget(searchBar);

    webEngineView = new WebEngineView(centralWidget);
    centralLayout->addWidget(webEngineView);

    this->setCentralWidget(centralWidget);
    this->showMaximized();
}

MainWindow::~MainWindow()
{

    delete ui;
}
