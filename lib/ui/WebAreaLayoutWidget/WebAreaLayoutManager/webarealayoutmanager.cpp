// Copyright (C) 2025 Mohit Deoli
// SPDX-License-Identifier: GPL-3.0-only


#include "webarealayoutmanager.h"
#include <QtGlobal>
// #include "ui_webarealayoutmanager.h"

WebAreaLayoutManager::WebAreaLayoutManager(QWidget *parent, const  QVector<QPointer<WebEngineView>> &_globalViewVector)
    : QWidget(parent),
    globalViewVector(_globalViewVector)
    /*, ui(new Ui::WebAreaLayoutManager)*/
{
    // ui->setupUi(this);
    horizontalLayout = new QHBoxLayout(this);
    layout()->setContentsMargins(0, 0, 0, 0);
    layout()->setSpacing(0);
}

WebAreaLayoutManager::~WebAreaLayoutManager()
{
    // delete ui;
}

void WebAreaLayoutManager::deleteWebView(WebEngineView *view){
    currentActiveViews.removeOne(view);
}

void WebAreaLayoutManager::addWebView(WebEngineView *view){

}

void WebAreaLayoutManager::applyLayout(int mode) {
    applyLayout(mode, globalViewVector);
}

void WebAreaLayoutManager::applyLayout(int mode, const QVector<QPointer<WebEngineView>> &views) {
    // clearLayout();
    currentActiveLayout = mode;
    switch(mode){
    case 0:
        currentActiveViews = views;
        setupSingle(currentActiveViews); // or just pass a WebEngineView* not a vector?
        break;
    case 1:
        // Filter views here
        if(views.size() < 2){
            currentActiveViews = views;
            // fallback to Single View
            setupSingle(currentActiveViews);
            emit message("Split view requires at least 2 tabs!");
            break;
        }else if(views.size() <= 4){
            currentActiveViews = views;
            setupSplit(currentActiveViews);
            break;
        }else{
            // Prompt user to choose : either based on recently visited or selection
            // Show a selection Dialog window
            TabSelectionDialog *tabSelectionDialog = new TabSelectionDialog(this, views);
            if (tabSelectionDialog->exec() == QDialog::Accepted) {
                currentActiveViews = tabSelectionDialog->getSelectedViews();
                tabSelectionDialog->deleteLater();
                setupSplit(currentActiveViews);
            }else{
                emit message("Split View can not be applied!");
            }
            break;
        }
        break;
    case 2:
        setupGrid(views);
        break;
    default:
        qDebug() << "Unsupported layout mode!";
    };
}


void WebAreaLayoutManager::clearLayout(bool free) {
    QLayout *l = layout();
    while(QLayoutItem *item = l->takeAt(0)){
        QWidget *w = item->widget();
        if(w){
            if(free) // TODO :Optimized it
                w->setParent(nullptr); // will freed OpenGL resources do this for tabs not active for long time
            else
                w->hide();
            l->removeWidget(w);
        }
        delete item; // we need to delete each LayoutItems explicitly
    }
}

void WebAreaLayoutManager::setupSingle(const QVector<QPointer<WebEngineView>> &views){
    if(layout() != horizontalLayout)
        this->setLayout(horizontalLayout);
    clearLayout(); // we don't gonna free OpenGL resourcces, but just hide it
    layout()->addWidget(views.at(0));
    WebEngineView *view = views.at(0);
    if (view->parent() != nullptr)
        view->show();
    else
        view->setParent(this);
}

void WebAreaLayoutManager::setupSplit(const QVector<QPointer<WebEngineView>>& views){
    clearLayout();
    if(layout() != horizontalLayout)
        this->setLayout(horizontalLayout);
    if (splitterLayout)
        splitterLayout->deleteLater();
    splitterLayout = new QSplitter(Qt::Horizontal, this);
    splitterLayout->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    for(WebEngineView *view : views){
        if (view->parent() != nullptr)
            view->show();
        else
            view->setParent(this);
        splitterLayout->addWidget(view);
    }
    horizontalLayout->addWidget(splitterLayout);

    // Equalize width
    if (splitterLayout->count() > 1) {
        QList<int> sizes;
        int width = splitterLayout->width() / splitterLayout->count();
        for (int i = 0; i < splitterLayout->count(); ++i) {
            sizes << width;
        }
        splitterLayout->setSizes(sizes);
    }
}

void WebAreaLayoutManager::setupGrid(const QVector<QPointer<WebEngineView>>& views){

}


void WebAreaLayoutManager::setCurrentWebArea(WebEngineView *view){
    if(view != currentSelectedView){
        currentSelectedView = view;
        switch(currentActiveLayout){
        case 0:
            applyLayout(0, QVector<QPointer<WebEngineView>>( { view })); //iff Single
            break;
        case 1:
             // If selected tab is already there, then ignore.
            if(currentActiveViews.indexOf(view) == -1){
                if(currentActiveViews.size()<4){
                    // If selected tab is not there + max capacity of Split view not fullfilled, then append
                    currentActiveViews.append(view);
                }
                else{
                    // If selected tab is not there + also max capacity of Split view is already fullfilled, then use intelligence or custom saved setting to append
                    currentActiveViews.takeAt(0);
                    currentActiveViews.append(view);
                    // as of now, replace it with first view
                    // TODO : Manupulate Current Active view
                }
                applyLayout(1, currentActiveViews);
                break;
            } // TODO : Optimized this block
        };
    }
}
