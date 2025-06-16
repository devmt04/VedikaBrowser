#include "navigationbar.h"
#include "ui_navigationbar.h"

#include <QDebug>

NavigationBar::NavigationBar(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::NavigationBar)
{
    /*
    NaviBarContainer (QWidget)
    └── QHBoxLayout (horizontalLayout)
        ├── NavigationButtonGroup (naviBtnGrp)
        └── SearchBar (searchBar)
    */
    // ui->setupUi(this);
    this->setObjectName("NaviBarContainer");
    this->setAttribute(Qt::WA_StyledBackground, true);

    horizontalLayout = new QHBoxLayout(this);
    this->setLayout(horizontalLayout);

    naviBtnGrp = new NavigationButtonGroup(this);
    searchBar = new SearchBar(this);

    connect(searchBar, &SearchBar::lineEditFocusIn, this, &NavigationBar::onSearchBarInFocus);
    connect(searchBar, &SearchBar::lineEditFocusOut, this, &NavigationBar::onSearchBarOutFocus);
    connect(searchBar, &SearchBar::lindEditReturnPress, this, &NavigationBar::onLineEditReturnPress);

    horizontalLayout->setContentsMargins(3,5,5,5); // int left, int top, int right, int bottom
    horizontalLayout->addWidget(naviBtnGrp);
    horizontalLayout->addWidget(searchBar);

    // TODO : Handle double click event to miniize/maximize the Browser's Window
}

NavigationBar::~NavigationBar()
{
    delete ui;
}

void NavigationBar::onSearchBarInFocus(){
    searchBar->setStyleSheet("QLineEdit#urlInputBar{background-color:#FDF6EC;placeholder-text-color:#7E4E1E;border:none;}");
    this->setStyleSheet("QWidget#SearchBarContainer{background-color:#FDF6EC;border:1px solid #FFDCA8;border-radius:7px}");
}

void NavigationBar::onSearchBarOutFocus(){
    searchBar->setStyleSheet("QLineEdit#urlInputBar{background-color:#FFDCA8;placeholder-text-color:#7E4E1E;border:none;}");
    this->setStyleSheet("QWidget#SearchBarContainer{background-color:#FFDCA8;border:none;border-radius:7px}");
}

void NavigationBar::onLineEditReturnPress(const QUrl &url)
{
    // Emit Signal to webview
    emit searchRequested(url);
}

void NavigationBar::setSearchbarText(const QString &text){
    searchBar->setInputBarText(text);
}
