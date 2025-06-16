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

    // TODO : FIX MARGIN AND ALIGNMENTS

    // DEBUG
    this->setObjectName("name1");
    this->setAttribute(Qt::WA_StyledBackground, true);
    this->setStyleSheet("QWidget#name1{border:1px solid blue;}");
    // DEBUG-END

    this->setFixedHeight(35);
    this->setMaximumWidth(150);
    this->setMinimumWidth(100);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    hboxLayout = new QHBoxLayout();
    hboxLayout->setContentsMargins(0,2,0,0); // left, top, right, bottom
    hboxLayout->setSpacing(10);
    this->setLayout(hboxLayout);

    favicon = new QLabel(this);
    title = new QLabel(this);
    closeTabButton = new QPushButton(QIcon(":/lib/resources/icon/cross_black.svg"), "", this);
    closeTabButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    QPixmap pixmap(":/lib/resources/icon/searchengines/google-color.svg");
    favicon->setPixmap(pixmap.scaled(
        favicon->size(),               // scale to label size
        Qt::KeepAspectRatio,          // maintain aspect ratio
        Qt::SmoothTransformation));   // smooth scaling
    favicon->setScaledContents(true);
    favicon->setFixedHeight(15);
    favicon->setFixedWidth(15);
    favicon->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    title->setText(QString("New Tab"));

    hboxLayout->addWidget(favicon);
    hboxLayout->addWidget(title);
    hboxLayout->addWidget(closeTabButton);
}

TabItem::~TabItem()
{
    delete ui;
}
