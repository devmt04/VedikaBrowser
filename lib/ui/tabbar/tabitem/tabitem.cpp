#include "tabitem.h"
#include "ui_tabitem.h"

TabItem::TabItem(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TabItem)
{
    // ui->setupUi(this);
    /*
    QHBoxLayout
    ├── QLabel (Icon/Favicon)
    ├── QLabel (Tab Title)
    └── QPushButton (Close)
    */
}

TabItem::~TabItem()
{
    delete ui;
}
