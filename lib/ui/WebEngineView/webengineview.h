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
    // QIcon getFavicon() const;

signals:
    void urlChanged(const QString &url, WebEngineView *senderView);
    void titleChanged(const QString &new_title);

private slots:
    void onUrlChanged(const QUrl &url);
    void onTitleChanged(const QString &title);

private:
    // Ui::WebEngineView *ui;
    QHBoxLayout *layout;
    QWebEngineView *webEngineView;
};

#endif // WEBENGINEVIEW_H
