// Copyright (C) 2025 Mohit Deoli
// SPDX-License-Identifier: GPL-3.0-only


#include "navigationbuttongroup.h"
#include "ui_navigationbuttongroup.h"

NavigationButtonGroup::NavigationButtonGroup(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::NavigationButtonGroup)
{
    /*
    NavigationBar (QWidget)
    └── QHBoxLayout (horizontalLayout)
        ├── backButton (QPushButton)
        ├── forwardButton (QPushButton)
        └── reloadButton (QPushButton)
    */

    // ui->setupUi(this);
    horizontalLayout = new QHBoxLayout(this);
    this->setLayout(horizontalLayout);

    backButton = new QPushButton(this);
    forwardButton = new QPushButton(this);
    reloadButton = new QPushButton(this);

    backButton->setProperty("class", "borderless");
    forwardButton->setProperty("class", "borderless");
    reloadButton->setProperty("class", "borderless");

    backButton->setIcon(QIcon(":/lib/resources/icon/arrow_back_light_inactive.svg"));
    forwardButton->setIcon(QIcon(":/lib/resources/icon/arrow_forward_light_inactive.svg"));
    reloadButton->setIcon(QIcon(":/lib/resources/icon/reload_light.svg"));

    connect(backButton, &QPushButton::clicked, this, [this](){
        emit back();
    });

    connect(forwardButton, &QPushButton::clicked, this, [this](){
        emit forward();
    });

    connect(reloadButton, &QPushButton::clicked, this, [this](){
        emit reload();
    });

    horizontalLayout->addWidget(backButton);
    horizontalLayout->addWidget(forwardButton);
    horizontalLayout->addWidget(reloadButton);
}

NavigationButtonGroup::~NavigationButtonGroup()
{
    delete ui;
}

void NavigationButtonGroup::unsetForward(){
    forwardButton->setIcon(QIcon(":/lib/resources/icon/arrow_forward_light_inactive.svg"));
};

void NavigationButtonGroup::unsetBackward(){
    backButton->setIcon(QIcon(":/lib/resources/icon/arrow_back_light_inactive.svg"));
};

void NavigationButtonGroup::setForward(){
    forwardButton->setIcon(QIcon(":/lib/resources/icon/arrow_forward_light.svg"));
};

void NavigationButtonGroup::setBackward(){
    backButton->setIcon(QIcon(":/lib/resources/icon/arrow_back_light.svg"));
};
