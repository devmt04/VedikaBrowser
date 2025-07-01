#include "navigationbar.h"
// Copyright (C) 2025 Mohit Deoli
// SPDX-License-Identifier: GPL-3.0-only


#include "ui_navigationbar.h"

NavigationBar::NavigationBar(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::NavigationBar)
{
    /*
    NaviBarContainer (QWidget)
    └── QHBoxLayout (horizontalLayout)
        ├── NavigationButtonGroup (naviBtnGrp)
        └── SearchBar (searchBar)
    */
    // ui->setupUi(this);

    this->setObjectName("NaviBarContainer");
    this->setAttribute(Qt::WA_StyledBackground, true);
    this->setMaximumHeight(43);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    horizontalLayout = new QHBoxLayout(this);
    this->setLayout(horizontalLayout);

    naviButtonGrp = new NavigationButtonGroup(this);
    searchBar = new SearchBar(this);
    webareaLayoutController = new WebAreaLayoutController(this);

    connect(searchBar, &SearchBar::lineEditFocusIn, this, &NavigationBar::onSearchBarInFocus);
    connect(searchBar, &SearchBar::lineEditFocusOut, this, &NavigationBar::onSearchBarOutFocus);
    connect(searchBar, &SearchBar::lindEditReturnPress, this, &NavigationBar::onLineEditReturnPress);

    connect(naviButtonGrp, &NavigationButtonGroup::back, this, [this](){
        emit pageBack();
    });
    connect(naviButtonGrp, &NavigationButtonGroup::forward, this, [this](){
        emit pageForward();
    });
    connect(naviButtonGrp, &NavigationButtonGroup::reload, this, [this](){
        emit pageReload();
    });

    connect(webareaLayoutController, &WebAreaLayoutController::indexChanged, this, [this](int index){
        emit layoutChanged(index);
    });

    horizontalLayout->setContentsMargins(3,5,5,5); // int left, int top, int right, int bottom
    horizontalLayout->addWidget(naviButtonGrp);
    horizontalLayout->addWidget(searchBar);
    horizontalLayout->addWidget(webareaLayoutController);

    // TODO : Handle double click event to miniize/maximize the Browser's Window
}

NavigationBar::~NavigationBar()
{
    delete ui;
}

void NavigationBar::setBackButtonState(bool active){
    if(active)
        naviButtonGrp->setBackward();
    else
        naviButtonGrp->unsetBackward();
}

void NavigationBar::setForwardButtonState(bool active){
    if(active)
        naviButtonGrp->setForward();
    else
        naviButtonGrp->unsetForward();
}

void NavigationBar::onSearchBarInFocus(){
    searchBar->setStyleSheet("QLineEdit#urlInputBar{background-color:#FDF6EC;placeholder-text-color:#7E4E1E;border:none;}");
    this->setStyleSheet("QWidget#SearchBarContainer{background-color:#FDF6EC;border:1px solid #FFDCA8;border-radius:13px}");
}

void NavigationBar::onSearchBarOutFocus(){
    searchBar->setStyleSheet("QLineEdit#urlInputBar{background-color:#FFDCA8;placeholder-text-color:#7E4E1E;border:none;}");
    this->setStyleSheet("QWidget#SearchBarContainer{background-color:#FFDCA8;border:none;border-radius:13px}");
}

void NavigationBar::onLineEditReturnPress(const QUrl &url)
{
    emit searchRequested(url);
}

void NavigationBar::setSearchbarText(const QString &text){
    searchBar->setInputBarText(text);
}

void NavigationBar::setMessage(const QString &text){
    const QString &originalText = searchBar->getInputBarText();
    searchBar->setInputBarText(text);

    QTimer *timer = new QTimer(this);
    timer->setSingleShot(true);
    connect(timer, &QTimer::timeout, this, [this, originalText, timer](){
        qDebug() << "timeout" ;
        searchBar->setInputBarText(originalText);
        timer->deleteLater();
    });
    timer->start(3500);
    // TODO : Animation
}


// TODO : use a mediator class for slot-signal connections ?
