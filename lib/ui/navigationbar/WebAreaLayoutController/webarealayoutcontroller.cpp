// Copyright (C) 2025 Mohit Deoli
// SPDX-License-Identifier: GPL-3.0-only

#include "webarealayoutcontroller.h"
// #include "ui_webarealayoutcontroller.h"

WebAreaLayoutController::WebAreaLayoutController(QWidget *parent)
    : QWidget(parent)
    /* , ui(new Ui::WebAreaLayoutController)*/
{
    // ui->setupUi(this);
    this->setObjectName("WebAreaLayoutControllerContainer");
    this->setAttribute(Qt::WA_StyledBackground, true);

    horizontalLayout = new QHBoxLayout(this);

    horizontalLayout->setContentsMargins(12, 0, 12, 0);

    controller = new QComboBox(this);
    controller->setObjectName("webAreaLayoutController");
    controller->setAttribute(Qt::WA_StyledBackground, true);
    controller->addItems({"Single View", "Split View", "Grid View", "Popup View"});
    connect(controller, &QComboBox::currentIndexChanged, this, [this](int index){
        emit indexChanged(index);
    });
    horizontalLayout->addWidget(controller);
    this->setLayout(horizontalLayout);
}

WebAreaLayoutController::~WebAreaLayoutController()
{
    // delete ui;
}

void WebAreaLayoutController::setComboBoxIndex(int index){
    controller->setCurrentIndex(index);
}
