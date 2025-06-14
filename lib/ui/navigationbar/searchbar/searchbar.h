#ifndef SEARCHBAR_H
#define SEARCHBAR_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QHBoxLayout>

namespace Ui {
class SearchBar;
}

class SearchBar : public QWidget
{
    Q_OBJECT

public:
    explicit SearchBar(QWidget *parent = nullptr);
    ~SearchBar();

private:
    Ui::SearchBar *ui;
    QHBoxLayout *searchbarLayout;
    QPushButton *searchEngineSwitchButton;
    QLineEdit *urlInputBar;
};

#endif // SEARCHBAR_H
