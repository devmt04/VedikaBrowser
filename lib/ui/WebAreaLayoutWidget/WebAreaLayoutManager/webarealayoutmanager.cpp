// Copyright (C) 2025 Mohit Deoli
// SPDX-License-Identifier: GPL-3.0-only


#include "webarealayoutmanager.h"

// #include "ui_webarealayoutmanager.h"
int count = 0;
WebAreaLayoutManager::WebAreaLayoutManager(QWidget *parent)
    : QWidget(parent)
    /*, ui(new Ui::WebAreaLayoutManager)*/
{
    // ui->setupUi(this);
    this->setLayout(new QHBoxLayout(this));
    layout()->setContentsMargins(0, 0, 0, 0);
    layout()->setSpacing(0);
}

WebAreaLayoutManager::~WebAreaLayoutManager()
{
    // delete ui;
}

void WebAreaLayoutManager::deleteWebView(WebEngineView *view){
    qDebug() << "2" << view;
    int index = currentActiveViews.indexOf(view);
    if(index != -1){ // iff Single // Optimized it
        qDebug() << "index " << index;
        currentActiveViews.takeAt(index);
    }
}

void WebAreaLayoutManager::addWebView(WebEngineView *view){
    currentSelectedView = view;
    switch(currentActiveLayout){
    case 0:
        QVector<WebEngineView*> views = { view };
        applyLayout(0, views);
    };
}

void WebAreaLayoutManager::applyLayout(int mode, const QVector<WebEngineView*>& views) {
    // clearLayout();
    currentActiveLayout = mode;
    switch(mode){
    case 0:
        // here
        currentActiveViews = views;
        setupSingle(currentActiveViews); // or just pass a WebEngineView* not a vector?
        break;
    case 1:
        // setupSplit(views);
        break;
    case 2:
        // setupGrid(views);
        break;
    default:
        qDebug() << "Unsupported layout mode!";
    };
}


void WebAreaLayoutManager::clearLayout(bool free) {
    qDebug() << "called";
    qDebug() << "layout count " << layout()->count();
    QLayout *l = layout();
    while(QLayoutItem *item = l->takeAt(0)){
        qDebug() << "removed";
        QWidget *w = item->widget();
        if(w){
            // w->setParent(nullptr); // will freed OpenGL resources do this for tabs not active for long time
            if(free) // TODO :Optimized it
                w->setParent(nullptr);
            else
                w->hide();
            l->removeWidget(w);
        }
        delete item; // we need to delete each LayoutItems explicitly
    }
}

void WebAreaLayoutManager::setupSingle(const QVector<WebEngineView*>& views){
    if(!views.isEmpty()){
        clearLayout(false); // we don't gonna free OpenGL resourcces, but just hide it
        layout()->addWidget(views.at(0));
        WebEngineView *view = views.at(0);
        if (view->parent() != nullptr)
            view->show();
        else
            view->setParent(this);
    }else{
        qDebug() << "Empty";
    }
}

void WebAreaLayoutManager::setupSplit(const QVector<WebEngineView*>& views){
    if(!views.isEmpty()){
        clearLayout(false);
        if(views.size() < 4){
            for(WebEngineView *v : views){
                layout()->addWidget(v);
            }
        }
    }
}

void WebAreaLayoutManager::setupGrid(const QVector<WebEngineView*>& views){

}


void WebAreaLayoutManager::setCurrentWebArea(WebEngineView *view){
    if(view != currentSelectedView){
        currentSelectedView = view;
        QVector<WebEngineView*> views = { view };
        // view->setParent(this);
        applyLayout(currentActiveLayout, views); //iff Single
    }
}
