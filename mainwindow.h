#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QVBoxLayout>
#include "./lib/ui/navigationbar/navigationbar.h"
#include "./lib/ui/WebEngineView/webengineview.h"

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
    void onSearchRequested(const QUrl &url);

private:
    Ui::MainWindow *ui;
    QVBoxLayout *centralLayout;
    NavigationBar *navigationBar;
    WebEngineView *webEngineView;
};
#endif // MAINWINDOW_H
