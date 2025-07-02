#include "tabselectiondialog.h"
// #include "ui_tabselectiondialog.h"

TabSelectionDialog::TabSelectionDialog(QWidget *parent, const QVector<WebEngineView*> &_globalViewVector, int _maxViews, int _minViews)
    : QDialog(parent),
    globalViewVector(_globalViewVector),
    maxViews(_maxViews),
    minViews(_minViews)
    /*, ui(new Ui::TabSelectionDialog)*/
{
    // ui->setupUi(this);
    this->setWindowTitle("Select Tabs");

    verticalLayout = new QVBoxLayout(this);
    this->setLayout(verticalLayout);

    viewCount = 0;

    scrollArea = new QScrollArea(this);
    gridContainer = new QWidget();
    gridLayout = new QGridLayout(gridContainer);

    gridContainer->setLayout(gridLayout);

    {
        int i = 0;
        for (WebEngineView* view : std::as_const(globalViewVector)){
            // Q_ASSERT(view);

            QCheckBox *check = new QCheckBox(view->getTitle(), gridContainer);
            gridLayout->addWidget(check, i / 4, i % 4);
            i++;
            connect(check, &QCheckBox::checkStateChanged, this, [=](Qt::CheckState state){
                if(state == Qt::Checked){
                    selectedViews.append(view);
                     viewCount++;
                }else{
                    selectedViews.removeOne(view); // will return false if not there
                    viewCount--;
                }
                if(viewCount >= maxViews) {
                    for (int j = 0; j < gridLayout->count(); ++j) {
                        QLayoutItem *item = gridLayout->itemAt(j);
                        QWidget *widget = item->widget();
                        if (QCheckBox *check = qobject_cast<QCheckBox *>(widget)){
                            if(!check->isChecked())
                                check->setDisabled(true);
                        }
                    }
                }else{
                    for (int j = 0; j < gridLayout->count(); ++j) {
                        QLayoutItem *item = gridLayout->itemAt(j);
                        QWidget *widget = item->widget();
                        if (QCheckBox *check = qobject_cast<QCheckBox *>(widget)){
                            if(!check->isEnabled())
                                check->setDisabled(false);
                        }
                    }
                }
            });
        }
    }

    scrollArea->setWidget(gridContainer);
    scrollArea->setWidgetResizable(true);
    verticalLayout->addWidget(scrollArea);

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    verticalLayout->addWidget(buttonBox);

    connect(buttonBox, &QDialogButtonBox::accepted, this, [this](){
        if(!viewCount<=minViews)
            this->accept();
        else
            qDebug() << "must be minimum";
        //TODO : Display msg on Dialog window
    });
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

TabSelectionDialog::~TabSelectionDialog()
{
    // delete ui;
}

QVector<WebEngineView*> TabSelectionDialog::getSelectedViews(){
    return selectedViews;
}
