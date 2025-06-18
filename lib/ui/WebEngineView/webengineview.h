#ifndef WEBENGINEVIEW_H
#define WEBENGINEVIEW_H

#include <QWidget>
#include <QHBoxLayout>
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
    void loadUrl(const QUrl &url);
    QUrl getUrl() const;

signals:
    void urlChanged(const QString &url);

private slots:
    void onUrlChanged(const QUrl &url);

private:
    // Ui::WebEngineView *ui;
    QHBoxLayout *layout;
    QWebEngineView *webEngineView;
};

#endif // WEBENGINEVIEW_H
