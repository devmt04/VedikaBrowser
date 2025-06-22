// Copyright (C) 2025 Mohit Deoli
// SPDX-License-Identifier: GPL-3.0-only


#ifndef WEBAREALAYOUTCONTROLLER_H
#define WEBAREALAYOUTCONTROLLER_H

#include <QWidget>
#include <QDebug>
#include <QHBoxLayout>
#include <QComboBox>

// namespace Ui {
// class WebAreaLayoutController;
// }

class WebAreaLayoutController : public QWidget
{
    Q_OBJECT

public:
    explicit WebAreaLayoutController(QWidget *parent = nullptr);
    ~WebAreaLayoutController();

signals:
    void indexChanged(int index);

private:
    // Ui::WebAreaLayoutController *ui;
    QHBoxLayout *horizontalLayout;
    QComboBox *controller;
};

#endif // WEBAREALAYOUTCONTROLLER_H
