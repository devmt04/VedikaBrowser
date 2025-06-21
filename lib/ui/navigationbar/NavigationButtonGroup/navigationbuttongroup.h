// Copyright (C) 2025 Mohit Deoli
// SPDX-License-Identifier: GPL-3.0-only


#ifndef NAVIGATIONBUTTONGROUP_H
#define NAVIGATIONBUTTONGROUP_H

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>

namespace Ui {
class NavigationButtonGroup;
}

class NavigationButtonGroup : public QWidget
{
    Q_OBJECT

public:
    explicit NavigationButtonGroup(QWidget *parent = nullptr);
    ~NavigationButtonGroup();
    void unsetForward();
    void unsetBackward();
    void setForward();
    void setBackward();

signals:
    void back();
    void forward();
    void reload();
    void stop(); // TODO

private:
    Ui::NavigationButtonGroup *ui;
    QHBoxLayout *horizontalLayout;
    QPushButton *backButton, *forwardButton, *reloadButton;
    // TODO : ADD HOME BUTTON, which directs to startup page
};

#endif // NAVIGATIONBUTTONGROUP_H
