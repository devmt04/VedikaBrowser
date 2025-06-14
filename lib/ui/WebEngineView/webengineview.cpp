#include "webengineview.h"
#include "ui_webengineview.h"

WebEngineView::WebEngineView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WebEngineView)
{
    // ui->setupUi(this);
    layout = new QVBoxLayout(this);
    webEngineView = new QWebEngineView(this);

    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(webEngineView);

    webEngineView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    webEngineView->load(QUrl("qrc:/lib/resources/webpages/startup_light.html"));
}

WebEngineView::~WebEngineView()
{
    delete ui;
}
