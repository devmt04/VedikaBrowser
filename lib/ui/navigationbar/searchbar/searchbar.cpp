#include "searchbar.h"
#include "ui_searchbar.h"

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
