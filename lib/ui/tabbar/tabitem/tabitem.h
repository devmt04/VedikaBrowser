#ifndef TABITEM_H
#define TABITEM_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QPixmap>

namespace Ui {
class TabItem;
}

class TabItem : public QWidget
{
    Q_OBJECT

public:
    // explicit TabItem(QWidget *parent = nullptr);
    explicit TabItem(QWidget *parent = nullptr,
                     const QString &title_string = "New Tab",
                     const QPixmap &pixmap = QPixmap(":/lib/resources/icon/searchengines/google-color.svg"));
    ~TabItem();

signals:
    void tabClosed(TabItem *self);

private slots:
    void onCloseButtonPressed();

private:
    // Ui::TabItem *ui;
    const QString tab_title;
    const QPixmap tab_pixmap;
    QHBoxLayout *hboxLayout;
    QLabel *favicon;
    QLabel *title;
    QPushButton *closeTabButton;

};

#endif // TABITEM_H
