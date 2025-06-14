#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // ui->setupUi(this);
    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* centralLayout = new QVBoxLayout(centralWidget);

    searchBar = new SearchBar(centralWidget);
    centralLayout->addWidget(searchBar);

    this->setCentralWidget(centralWidget);
    this->showMaximized();
}

MainWindow::~MainWindow()
{

    delete ui;
}
