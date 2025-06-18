#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QMap>
#include "./lib/ui/navigationbar/navigationbar.h"
#include "./lib/ui/WebEngineView/webengineview.h"
#include "./lib/ui/tabbar/tabbar.h"
#include "./lib/ui/tabbar/tabitem/tabitem.h"

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
    void onNewTabAdded(TabItem *tab);
    void onTabClosed(TabItem *tab);
    void onTabSelected(TabItem *tab);

private:
    // Ui::MainWindow *ui;
    int init_tabCount = 0;
    QVBoxLayout *centralLayout;
    // FramelessWindow<MainWindow> *window;
    TabBar *tabBar;
    NavigationBar *navigationBar;
    QStackedWidget *stackedWebArea;
    WebEngineView *defaultWebEngineView;
    WebEngineView *currentWebEngineView;
    QMap<TabItem*, WebEngineView*> tabMap;
};
#endif // MAINWINDOW_H
