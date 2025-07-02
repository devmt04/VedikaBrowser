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
        └── WebAreaLayoutController (webareaLayoutController)
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
    searchBar->setProperty("state", "focused");
    searchBar->style()->unpolish(searchBar);
    searchBar->style()->polish(searchBar);
}

void NavigationBar::onSearchBarOutFocus(){
    searchBar->setProperty("state", "");
    searchBar->style()->unpolish(searchBar);
    searchBar->style()->polish(searchBar);
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

void NavigationBar::setLayoutControllerIndex(int index){
    webareaLayoutController->setComboBoxIndex(index);
}

// TODO : use a mediator class for slot-signal connections ?
