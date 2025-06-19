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


void WebEngineView::onUrlChanged(const QUrl &url){
    // use lambda instead
    emit urlChanged(url.toDisplayString(), this);
}

void WebEngineView::onTitleChanged(const QString &title){
    emit titleChanged(title);
}

