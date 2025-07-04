#ifndef TABSELECTIONDIALOG_H
#define TABSELECTIONDIALOG_H

#include <QWidget>
#include <QDebug>
#include <QVector>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QScrollArea>
#include <QCheckBox>
#include <QDialog>
#include <QDialogButtonBox>

#include "../../WebEngineView/webengineview.h"

// namespace Ui {
// class TabSelectionDialog;
// }

class TabSelectionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TabSelectionDialog(QWidget *parent, const QVector<WebEngineView*> &_globalViewVector, int _maxViews, int _minViews);
    ~TabSelectionDialog();
    QVector<WebEngineView*> getSelectedViews();

private:
    // Ui::TabSelectionDialog *ui;
    const QVector<WebEngineView*> &globalViewVector;
    int maxViews, minViews, viewCount;
    QVector<WebEngineView*> selectedViews;
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea;
    QGridLayout *gridLayout;
    QWidget *gridContainer;
    QDialogButtonBox *buttonBox;
};

#endif // TABSELECTIONDIALOG_H
