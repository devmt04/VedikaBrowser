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
}

WebEngineView::~WebEngineView()
{
    // delete ui;
}

void WebEngineView::loadUrl(QUrl url){
    webEngineView->load(url);
    webEngineView->setFocus();
}

void WebEngineView::onUrlChanged(const QUrl &url){
    // use lambda instead
    emit urlChanged(url.toDisplayString());
}
