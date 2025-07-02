// Copyright (C) 2025 Mohit Deoli
// SPDX-License-Identifier: GPL-3.0-only


#include "tabitem.h"
#include "ui_tabitem.h"
#include <QDebug>
#include <QStyle>

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
    this->setObjectName("TabItem");
    this->setAttribute(Qt::WA_StyledBackground, true);

    this->setFixedHeight(35);
    this->setMaximumWidth(220);
    this->setMinimumWidth(70);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    hboxLayout = new QHBoxLayout();
    hboxLayout->setContentsMargins(0,2,0,0); // left, top, right, bottom
    // hboxLayout->setSpacing(10);
    this->setLayout(hboxLayout);

    favicon = new QLabel(this);
    title = new QLabel(this);

    closeTabButton = new QPushButton(QIcon(":/lib/resources/icon/cross_light.svg"), "", this);
    closeTabButton->setIconSize(QSize(12, 12));
    closeTabButton->setFixedSize(20, 20);
    closeTabButton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    closeTabButton->setObjectName("closeTabButton");
    // closeTabButton->setContentsMargins(3,0,3,0);
    connect(closeTabButton, &QPushButton::clicked, this, &TabItem::onCloseButtonPressed);

    favicon->setPixmap(tab_pixmap.scaled(
        favicon->size(),               // scale to label size
        Qt::KeepAspectRatio,          // maintain aspect ratio
        Qt::SmoothTransformation));   // smooth scaling
    favicon->setScaledContents(true);
    favicon->setFixedHeight(14);
    favicon->setFixedWidth(14);
    favicon->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    // favicon->setContentsMargins(3,0,0,0);

    title->setText(tab_title);
    title->setObjectName("TabBarTitle");
    // title->setStyleSheet("QLabel#title{border:1px solid blue}");
    title->setMinimumWidth(30);
    title->setMaximumWidth(150);
    title->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);


    // title->setContentsMargins(10,0,3,0);

    // favicon->setContentsMargins(5, 0, 0, 0);
   // title->setContentsMargins(5, 0, 5, 0);
   // closeTabButton->setContentsMargins(5, 0, 5, 0);
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

void TabItem::mousePressEvent(QMouseEvent *event){
    QWidget::mousePressEvent(event); // Preserves base behaviour
    emit tabClicked(this);
}

void TabItem::setTitle(const QString &new_title){
    title->setText(new_title);
}

void TabItem::setFavicon(const QPixmap &new_pixmap){
    if(!new_pixmap.isNull()){
        favicon->setPixmap(new_pixmap.scaled(
            favicon->size(),               // scale to label size
            Qt::KeepAspectRatio,          // maintain aspect ratio
            Qt::SmoothTransformation));
    }else{
        favicon->setPixmap(QPixmap(":/lib/resources/icon/favicon_load_black.svg").scaled(
            favicon->size(),               // scale to label size
            Qt::KeepAspectRatio,          // maintain aspect ratio
            Qt::SmoothTransformation));
    }

    // TODO : Show loading animation while favicon is loaded i.e, is null
        // cache favicon for frequently visited sites
}

void TabItem::setSelected(bool selected){
    if (selected){
        this->setProperty("selected", "true");
        this->style()->unpolish(this);
        this->style()->polish(this);

        title->setProperty("selected", "true");
        title->style()->unpolish(title);
        title->style()->polish(title);
    }
    else{
        this->setProperty("selected", "false");
        this->style()->unpolish(this);
        this->style()->polish(this);

        title->setProperty("selected", "false");
        title->style()->unpolish(title);
        title->style()->polish(title);
    }
}
