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

    void setTitle(const QString &new_title);

signals:
    void tabClosed(TabItem *self);
    void tabClicked(TabItem *self);

private slots:
    void onCloseButtonPressed();

protected:
    void mousePressEvent(QMouseEvent *event) override;

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
