#include "searchbar.h"
#include "ui_searchbar.h"
#include <QDebug>

SearchBar::SearchBar(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SearchBar)
{

    // ui->setupUi(this); // Nothing in it's .ui file as of now

    this->setObjectName("SearchBarContainer");
    this->setAttribute(Qt::WA_StyledBackground, true);

    searchbarLayout = new QHBoxLayout(this);
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

QLineEdit* SearchBar::getLineEdit(){
    return urlInputBar;
}


bool SearchBar::eventFilter(QObject *watched, QEvent *event){
    if(watched == urlInputBar && event->type() == QEvent::FocusIn){
        emit lineEditFocusIn();
    }else if(watched == urlInputBar && event->type() == QEvent::FocusOut){
        emit lineEditFocusOut();
    }
    return QWidget::eventFilter(watched, event);
}
