// Copyright (C) 2025 Mohit Deoli
// SPDX-License-Identifier: GPL-3.0-only


#include "webarealayoutmanager.h"
#include <QtGlobal>
// #include "ui_webarealayoutmanager.h"

WebAreaLayoutManager::WebAreaLayoutManager(QWidget *parent, const QVector<WebEngineView*> &_globalViewVector)
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
    //
}

void WebAreaLayoutManager::applyLayout(int mode) {
    applyLayout(mode, globalViewVector);
}

void WebAreaLayoutManager::applyLayout(int mode, const QVector<WebEngineView*> &views) {
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
            // will fallback to Single View
            emit message("Split view requires at least 2 tabs!", mode);
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
                emit message("Split View can not be applied!", mode);
            }
            break;
        }
        break;
    case 2:
        // As of now, it suppoorts only 4 tabs at max
        // Need atleast 4 views
        if(views.size() < 4){
            emit message("Grid view requires at least 4 tabs!", mode);
            break;
        }else if(views.size() == 4){
            currentActiveViews = views;
            setupGrid(currentActiveViews);
            break;
        }else{
            TabSelectionDialog *tabSelectionDialog = new TabSelectionDialog(this, views);
            if (tabSelectionDialog->exec() == QDialog::Accepted) {
                currentActiveViews = tabSelectionDialog->getSelectedViews();
                tabSelectionDialog->deleteLater();
                setupGrid(currentActiveViews);
            }else{
                emit message("Grid View can not be applied!", mode);
            }
            break;
        }
        break;
    default:
        qDebug() << "Unsupported layout mode!";
    };
}


void WebAreaLayoutManager::clearLayout(bool free) {
    QLayout *l = layout();
    // So this layout can only have a QWidget
    // Now that QWidget can be QSpillter or GridContainer
    // Hiding these widgets, will also hide their childs, so we not need to explicitly hide all WebEngineView
    while(QLayoutItem *item = l->takeAt(0)){
        QWidget *w = item->widget();
        if(w){
            if(free){ // TODO : Optimization required
                w->setParent(nullptr); // will freed OpenGL resources do this for tabs not active for long time
            }else{
                w->hide();
            }
            l->removeWidget(w);
        }
        delete item; // we need to delete each LayoutItems explicitly
    }
}

void WebAreaLayoutManager::setupSingle(const QVector<WebEngineView*> &views){
    clearLayout(); // we don't gonna free OpenGL resourcces, but just hide the widget
    layout()->addWidget(views.at(0));
    WebEngineView *view = views.at(0);
    if (view->parent() != nullptr)
        view->show();
    else
        view->setParent(this); // ?
}

void WebAreaLayoutManager::setupSplit(const QVector<WebEngineView*>& views){
    clearLayout();
    if (splitterLayout){
        for(WebEngineView *view : splitterLayout->findChildren<WebEngineView*>()){
            view->setParent(this); // reparent views to their original parent
        }
        splitterLayout->deleteLater();
        splitterLayout = nullptr;
    }

    splitterLayout = new QSplitter(Qt::Horizontal, this);
    splitterLayout->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    for(WebEngineView *view : views){
        splitterLayout->addWidget(view); //  Add to splitter (temporarily changes parent)
        if (view->parent() != nullptr)
            view->show();
        else
            view->setParent(this); // ?
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

void WebAreaLayoutManager::setupGrid(const QVector<WebEngineView*>& views){
    clearLayout();
    if(gridContainer){
        for(WebEngineView *view : gridContainer->findChildren<WebEngineView*>()){
            view->setParent(this);
        }
        gridContainer->deleteLater();
    }
    gridContainer = new QWidget(this);
    gridLayout = new QGridLayout(gridContainer);

    gridContainer->setObjectName("gridViewContainer");
    gridContainer->setAttribute(Qt::WA_StyledBackground, true);
    gridContainer->setProperty("theme", "dark");
    gridContainer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    gridLayout->setContentsMargins(0,0,0,0);
    gridLayout->setSpacing(1);

    int i = 0;
    for(WebEngineView *view : views){
        gridLayout->addWidget(view, i / 2, i % 2);
        if (view->parent() != nullptr)
            view->show();
        else
            view->setParent(this); // ?
        i++;
    }

    gridContainer->setLayout(gridLayout);
    horizontalLayout->addWidget(gridContainer);
}


void WebAreaLayoutManager::setCurrentWebArea(WebEngineView *view){
    if(view != currentSelectedView){
        currentSelectedView = view;
        switch(currentActiveLayout){
        case 0:
            applyLayout(0, QVector<WebEngineView*>( { view }));
            break;
        case 1:
             // If selected tab is already there, then ignore.
            if(currentActiveViews.indexOf(view) == -1){
                if(currentActiveViews.size()<4){
                    // If selected tab is not there + max capacity of Split view NOT fullfilled, then append
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
            break;
        case 2:
            // TODO : More work here
            if(currentActiveViews.indexOf(view) == -1){
                if(currentActiveViews.size()>=4){
                    currentActiveViews.takeAt(0);
                    currentActiveViews.append(view);
                    // TODO : merge logic for case 1 and 2
                }
                applyLayout(2, currentActiveViews);
                break;
            }
            break;
        };
    }
}

//TODO : Instead of apply whole layout again, just replace particular views!
