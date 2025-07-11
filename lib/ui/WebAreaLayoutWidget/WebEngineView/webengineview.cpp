// Copyright (C) 2025 Mohit Deoli
// SPDX-License-Identifier: GPL-3.0-only


#include "webengineview.h"
#include "ui_webengineview.h"

WebEngineView::WebEngineView(QWidget *parent)
    : QWidget(parent)
    /*, ui(new Ui::WebEngineView)*/
{
    /*
    WebEngineContainer (QWidget)
    └── QHBoxLayout (layout)
        └── QWebEngineView (webEngineView)

    TODO : Replace QHBoxLayout with a custom layout
    */
    // ui->setupUi(this);
    layout = new QHBoxLayout(this);
    webEngineView = new QWebEngineView(this);

    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(webEngineView);

    webEngineView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    webEngineView->load(QUrl("qrc:/lib/resources/webpages/startup_light.html"));

    connect(webEngineView, &QWebEngineView::urlChanged,this, &WebEngineView::onUrlChanged);
    connect(webEngineView, &QWebEngineView::titleChanged, this, &WebEngineView::onTitleChanged);
    connect(webEngineView, &QWebEngineView::iconChanged, this, &WebEngineView::onFaviconChanged);
}

WebEngineView::~WebEngineView()
{
    // delete ui;
}

void WebEngineView::loadUrl(const QUrl &url){
    webEngineView->load(url);
    webEngineView->setFocus();
}

QUrl WebEngineView::getUrl() const {
    return webEngineView->url();
}

QString WebEngineView::getTitle() const{
    return webEngineView->title();
}

void WebEngineView::back(){
    if (webEngineView->history()->canGoBack()) {
        webEngineView->back();
    }
}

void WebEngineView::forward(){
    if (webEngineView->history()->canGoForward()) {
        webEngineView->forward();
    }
}


void WebEngineView::reload(){
    webEngineView->reload();
}

void WebEngineView::onUrlChanged(const QUrl &url){
    // use lambda instead
    // sending senderView in case multiple WebEngineView emit at same time
    emit urlChanged(url.toDisplayString());
    emit backButtonState(webEngineView->history()->canGoBack());
    emit forwardButtonState(webEngineView->history()->canGoForward());
}

void WebEngineView::onTitleChanged(const QString &title){
    emit titleChanged(title);
}

void WebEngineView::onFaviconChanged(const QIcon &new_favicon){
    emit faviconChanged(new_favicon);
}

