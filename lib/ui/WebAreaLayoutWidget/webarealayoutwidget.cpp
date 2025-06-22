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
    stackedWebArea = new QStackedWidget(this);
    horizontalLayout->addWidget(stackedWebArea);

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
    WebEngineView *newWebWidget = new WebEngineView(stackedWebArea);
    stackedWebArea->addWidget(newWebWidget);
    stackedWebArea->setCurrentWidget(newWebWidget);

    webEngineViewVector.insert(index, newWebWidget);
    // int dynamicIndex = webEngineViewVector.indexOf(newWebWidget);
    connect(newWebWidget, &WebEngineView::urlChanged, this, [this](const QUrl &url){
        emit webViewUrlChanged(url.toDisplayString());
    });
    connect(newWebWidget, &WebEngineView::titleChanged, this, [=](const QString &new_title){

        emit webViewTitleChanged(webEngineViewVector.indexOf(newWebWidget), new_title);
    });
    connect(newWebWidget, &WebEngineView::faviconChanged, this, [=](const QIcon &favicon){
        emit webViewFaviconChanged( webEngineViewVector.indexOf(newWebWidget), favicon);
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
    WebEngineView *view = webEngineViewVector.takeAt(index);
    stackedWebArea->removeWidget(view);
    view->deleteLater();
}

void WebAreaLayoutWidget::setCurrentWebView(int index){
    WebEngineView *view = webEngineViewVector.at(index);
    stackedWebArea->setCurrentWidget(view);
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

// WebEngineView* WebAreaLayoutWidget::currentWebView() const{

// }

QUrl WebAreaLayoutWidget::currentUrl() const{
    return currentWebEngineView->getUrl();
}

void WebAreaLayoutWidget::setLayoutMode(LayoutMode mode){
    switch (mode) {
    case LayoutMode::Single:
        qDebug() << "Sngle";
        break;
    case LayoutMode::Split:
        qDebug() << "Split";
        break;
    case LayoutMode::Grid:
        qDebug() << "Grid";
        break;
    case LayoutMode::Popup:
        qDebug() << "Popup";
        break;
    }
}
