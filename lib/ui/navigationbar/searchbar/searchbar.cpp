// Copyright (C) 2025 Mohit Deoli
// SPDX-License-Identifier: GPL-3.0-only


#include "searchbar.h"
#include "ui_searchbar.h"
#include <QDebug>

SearchBar::SearchBar(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SearchBar)
{

    // ui->setupUi(this); // Nothing in it's .ui file as of now
    /*
    SearchBarContainer (QWidget)
    └── QHBoxLayout (searchbarLayout)
        ├── QPushButton (searchEngineSwitchButton)
        └── QLineEdit (urlInputBar)
    */
    this->setObjectName("SearchBarContainer");
    this->setAttribute(Qt::WA_StyledBackground, true);

    searchbarLayout = new QHBoxLayout(this);
    this->setLayout(searchbarLayout);
    searchbarLayout->setContentsMargins(8, 0, 8, 0);

    searchEngineSwitchButton = new QPushButton(this);
    urlInputBar = new QLineEdit(this);

    // Search Engine Switch Button Properties
    searchEngineSwitchButton->setProperty("class", "borderless");
    searchEngineSwitchButton->setIcon(QIcon(":/lib/resources/icon/searchengines/google-color.svg"));

    // Input Bar Properties
    urlInputBar->installEventFilter(this);
    urlInputBar->setObjectName("urlInputBar");
    urlInputBar->setPlaceholderText(QStringLiteral("Search with Google or type a URL"));

    // Horizontal Layout Prroperties
    searchbarLayout->setObjectName("searchbarLayout");

    searchbarLayout->addWidget(searchEngineSwitchButton);
    searchbarLayout->addWidget(urlInputBar);
}

SearchBar::~SearchBar()
{
    delete ui;
}

QString SearchBar::getInputBarText() const{
    return urlInputBar->text();
}

void SearchBar::setInputBarText(const QString &text){
    if (QString::compare(text, "qrc:/lib/resources/webpages/startup_light.html", Qt::CaseSensitive) != 0) {
        urlInputBar->setText(text);
        urlInputBar->setCursorPosition(0);
        //TODO-FIX: After calling setCursorPosition() the cursor is still visible when QLineEdit is out of foucs
    }else{
        urlInputBar->clear();
    }
}

bool SearchBar::eventFilter(QObject *watched, QEvent *event){
    if(watched == urlInputBar && event->type() == QEvent::FocusIn){
        urlInputBar->setProperty("state", "focused");
        urlInputBar->style()->unpolish(urlInputBar);
        urlInputBar->style()->polish(urlInputBar);
        // update();
        emit lineEditFocusIn();
        return true;
    }else if(watched == urlInputBar && event->type() == QEvent::FocusOut){
        urlInputBar->setProperty("state", "");
        urlInputBar->style()->unpolish(urlInputBar);
        urlInputBar->style()->polish(urlInputBar);
        emit lineEditFocusOut();
        return true;
    }else if(watched == urlInputBar && event->type() == QEvent::KeyPress){
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event); // static_cast is a compile-time cast, here it cast, QEvent* to QKeyEvent*
        if(keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter){
            emit lindEditReturnPress(SearchBar::processQuery(urlInputBar->text()));
            return true; // done processing of event
        }
    }
    return QWidget::eventFilter(watched, event); // Let Qt process the event further as per it's implimentation
}



QUrl SearchBar::processQuery(const QString &query){
    // use QUrl::fromUserInput()
    QUrl encodedUrl;
    if(!query.isEmpty()){
        if(!isUrl(query)){
            qDebug("invalid url\n");
            encodedUrl = strToGoogleUrl(query);
        }else{
            qDebug("valid url\n");
            encodedUrl = QUrl(query.toUtf8());
        }
    }
    return encodedUrl;
}


bool SearchBar::isUrl(const QString &query){
    /*
`   Rule : If containing spaces, then not a url
           If not starts with http:// or https:// (as of now) then not a url
    */
    if (query.split(' ').size() > 1) {
        return false;
    }
    if (!query.startsWith("http://") && !query.startsWith("https://")) {
        return false;
    }
    return true;

    // Check for query start with www. and add protocols to them
    // check for IPs and localhost

    /*
    Or using

    QUrl url = QUrl::fromUserInput(query);
    if (url.isValid() && !query.contains(' ')) {
        return true;  // Treat as URL
    } else {
        return false; // Treat as search query
    }
    */
}

QUrl SearchBar::strToGoogleUrl(const QString &query){
    return QUrl("https://www.google.com/search?q=" + QUrl::toPercentEncoding(query));
}


