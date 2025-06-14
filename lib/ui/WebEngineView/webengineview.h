#ifndef WEBENGINEVIEW_H
#define WEBENGINEVIEW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QtWebEngineWidgets/QWebEngineView>
namespace Ui {
class WebEngineView;
}

class WebEngineView : public QWidget
{
    Q_OBJECT

public:
    explicit WebEngineView(QWidget *parent = nullptr);
    ~WebEngineView();

private:
    Ui::WebEngineView *ui;
    QVBoxLayout *layout;
    QWebEngineView *webEngineView;
};

#endif // WEBENGINEVIEW_H
