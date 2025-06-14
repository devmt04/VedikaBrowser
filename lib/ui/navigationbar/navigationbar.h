#ifndef NAVIGATIONBAR_H
#define NAVIGATIONBAR_H

#include <QWidget>
#include <QHBoxLayout>

#include "./searchbar/searchbar.h"
#include "./NavigationButtonGroup/navigationbuttongroup.h"

namespace Ui {
class NavigationBar;
}

class NavigationBar : public QWidget
{
    Q_OBJECT

public:
    explicit NavigationBar(QWidget *parent = nullptr);
    ~NavigationBar();

signals:
    void searchRequested(const QUrl &url);

public slots:
    void setSearchbarText(const QString &text);

private slots:
    void onSearchBarInFocus();
    void onSearchBarOutFocus();
    void onLineEditReturnPress(const QUrl &url);

// protected:
//    bool eventFilter(QObject *watched, QEvent *event) override;
//      // called for every event received by an object(obj in this case) that this class is filtering

private:
    Ui::NavigationBar *ui;
    QHBoxLayout *horizontalLayout;
    NavigationButtonGroup *naviBtnGrp;
    SearchBar *searchBar;
};

#endif // NAVIGATIONBAR_H
