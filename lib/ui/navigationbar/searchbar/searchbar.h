#ifndef SEARCHBAR_H
#define SEARCHBAR_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QEvent>

namespace Ui {
class SearchBar;
}

class SearchBar : public QWidget
{
    Q_OBJECT

public:
    explicit SearchBar(QWidget *parent = nullptr);
    QLineEdit *getLineEdit();
    ~SearchBar();

signals:
    void lineEditFocusIn();
    void lineEditFocusOut();

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    Ui::SearchBar *ui;
    QHBoxLayout *searchbarLayout;
    QPushButton *searchEngineSwitchButton;
    QLineEdit *urlInputBar;
};

#endif // SEARCHBAR_H
