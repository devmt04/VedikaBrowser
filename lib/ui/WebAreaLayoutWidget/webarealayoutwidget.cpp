// Copyright (C) 2025 Mohit Deoli
// SPDX-License-Identifier: GPL-3.0-only


#include "webarealayoutwidget.h"
// #include "ui_webarealayoutwidget.h"

WebAreaLayoutWidget::WebAreaLayoutWidget(QWidget *parent)
    : QWidget(parent)
    /*, ui(new Ui::WebAreaLayoutWidget)*/
{
    // ui->setupUi(this);
    horizontalLayout = new QHBoxLayout(this);
    // stackedWebArea = new QStackedWidget(this);
    layoutManager = new WebAreaLayoutManager(this);
    horizontalLayout->addWidget(layoutManager);

    horizontalLayout->setContentsMargins(0, 0, 0, 0);
    horizontalLayout->setSpacing(0);

    this->setLayout(horizontalLayout);
}

WebAreaLayoutWidget::~WebAreaLayoutWidget()
{
    // delete ui;
}

int WebAreaLayoutWidget::webviewVectorSize() const{
    return webEngineViewVector.size();
}

void WebAreaLayoutWidget::addNewWebView(int index){
    WebEngineView *newWebWidget = new WebEngineView(layoutManager);

    layoutManager->addWebView(newWebWidget);

    // stackedWebArea->addWidget(newWebWidget);
    // stackedWebArea->setCurrentWidget(newWebWidget);

    webEngineViewVector.insert(index, newWebWidget);
    connect(newWebWidget, &WebEngineView::urlChanged, this, [this](const QUrl &url){
        emit webViewUrlChanged(url.toDisplayString());
    });
    connect(newWebWidget, &WebEngineView::titleChanged, this, [=](const QString &new_title){
        emit webViewTitleChanged(webEngineViewVector.indexOf(newWebWidget), new_title);
    });
    connect(newWebWidget, &WebEngineView::faviconChanged, this, [=](const QIcon &favicon){
        emit webViewFaviconChanged(webEngineViewVector.indexOf(newWebWidget), favicon);
    });
    connect(newWebWidget, &WebEngineView::backButtonState, this, [=](bool enabled){
        if(newWebWidget == currentWebEngineView)
            emit backButtonState(enabled);
    });
    connect(newWebWidget, &WebEngineView::forwardButtonState, this, [=](bool enabled){
        if(newWebWidget == currentWebEngineView)
            emit forwardButtonState(enabled);
    });
}

void WebAreaLayoutWidget::closeWebView(int index){
    qDebug() << "1 "<< index;
    WebEngineView *view = webEngineViewVector.takeAt(index);
    layoutManager->deleteWebView(view);
    // stackedWebArea->removeWidget(view);
    view->deleteLater();
}

void WebAreaLayoutWidget::setCurrentWebView(int index){
    WebEngineView *view = webEngineViewVector.at(index);
    layoutManager->setCurrentWebArea(view);
    // stackedWebArea->setCurrentWidget(view);
    currentWebEngineView = view;
}

void WebAreaLayoutWidget::loadUrl(const QUrl &url){
    currentWebEngineView->loadUrl(url);
}

void WebAreaLayoutWidget::goBack(){
    if(currentWebEngineView!=nullptr){
        currentWebEngineView->back();
    }
}

void WebAreaLayoutWidget::goForward(){
    if(currentWebEngineView!=nullptr){
        currentWebEngineView->forward();
    }
}


QUrl WebAreaLayoutWidget::currentUrl() const{
    return currentWebEngineView->getUrl();
}

void WebAreaLayoutWidget::setLayoutMode(int mode){
    switch (mode) {
    case 0:
        qDebug() << "Sngle";
        layoutManager->applyLayout(mode, webEngineViewVector);
        break;
    case 1:
        qDebug() << "Split";
        layoutManager->applyLayout(mode, webEngineViewVector);
        break;
    case 2:
        qDebug() << "Grid";
        layoutManager->applyLayout(mode, webEngineViewVector);
        break;
    case 3:
        qDebug() << "Popup";
        layoutManager->applyLayout(mode, webEngineViewVector);
        break;
    } // TODO Unify them if using int

    // TODO : Track recently visited tabs in order to send them to layoutManager
}
