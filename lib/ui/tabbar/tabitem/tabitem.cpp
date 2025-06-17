#include "tabitem.h"
#include "ui_tabitem.h"
#include <QDebug>

TabItem::TabItem(QWidget *parent, const QString &title_string, const QPixmap &pixmap)
    : QWidget(parent)
    /*, ui(new Ui::TabItem)*/
    , tab_title(title_string)
    , tab_pixmap(pixmap)
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
    this->setMinimumWidth(70);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    hboxLayout = new QHBoxLayout();
    hboxLayout->setContentsMargins(0,2,0,0); // left, top, right, bottom
    hboxLayout->setSpacing(10);
    this->setLayout(hboxLayout);

    favicon = new QLabel(this);
    title = new QLabel(this);

    closeTabButton = new QPushButton(QIcon(":/lib/resources/icon/cross_black.svg"), "", this);
    closeTabButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    connect(closeTabButton, &QPushButton::clicked, this, &TabItem::onCloseButtonPressed);

    // QPixmap pixmap(":/lib/resources/icon/searchengines/google-color.svg");
    favicon->setPixmap(tab_pixmap.scaled(
        favicon->size(),               // scale to label size
        Qt::KeepAspectRatio,          // maintain aspect ratio
        Qt::SmoothTransformation));   // smooth scaling
    favicon->setScaledContents(true);
    favicon->setFixedHeight(15);
    favicon->setFixedWidth(15);
    favicon->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    title->setText(tab_title);

    hboxLayout->addWidget(favicon);
    hboxLayout->addWidget(title);
    hboxLayout->addWidget(closeTabButton);
}

TabItem::~TabItem()
{
    // delete ui;
}


void TabItem::onCloseButtonPressed(){
    emit tabClosed(this);
}

