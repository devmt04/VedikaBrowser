// Copyright (C) 2025 Mohit Deoli
// SPDX-License-Identifier: GPL-3.0-only


#ifndef SEARCHBAR_H
#define SEARCHBAR_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QEvent>
#include <QKeyEvent>

namespace Ui {
class SearchBar;
}

class SearchBar : public QWidget
{
    Q_OBJECT

public:
    explicit SearchBar(QWidget *parent = nullptr);
    ~SearchBar();
    void setInputBarText(const QString &text);

signals:
    void lineEditFocusIn();
    void lineEditFocusOut();
    void lindEditReturnPress(const QUrl &url);

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    Ui::SearchBar *ui;
    QHBoxLayout *searchbarLayout;
    QPushButton *searchEngineSwitchButton;
    QLineEdit *urlInputBar;

    QUrl processQuery(const QString &query);
    bool isUrl(const QString &query);
    QUrl strToGoogleUrl(const QString &query);
};

#endif // SEARCHBAR_H
