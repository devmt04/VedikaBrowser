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
    explicit TabItem(QWidget *parent = nullptr);
    ~TabItem();

private:
    Ui::TabItem *ui;
    QHBoxLayout *hboxLayout;
    QLabel *favicon;
    QLabel *title;
    QPushButton *closeTabButton;

};

#endif // TABITEM_H
