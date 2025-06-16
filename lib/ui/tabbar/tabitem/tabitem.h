#ifndef TABITEM_H
#define TABITEM_H

#include <QWidget>

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
};

#endif // TABITEM_H
