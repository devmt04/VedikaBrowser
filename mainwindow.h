#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>

#include <QVBoxLayout>

#include <QUrl>
#include <QtWebEngineWidgets/QWebEngineView>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_gobutton_clicked();

private:
    Ui::MainWindow *ui;
    QPushButton *gobutton, *backbutton, *forwardbutton, *reloadbutton;
    QWebEngineView *view;
    QLineEdit *searchbar;

};
#endif // MAINWINDOW_H
