#include "tabselectiondialog.h"
// #include "ui_tabselectiondialog.h"

TabSelectionDialog::TabSelectionDialog(QWidget *parent, const QVector<WebEngineView*> &_globalViewVector)
    : QDialog(parent),
    globalViewVector(_globalViewVector)
    /*, ui(new Ui::TabSelectionDialog)*/
{
    // ui->setupUi(this);
    this->setWindowTitle("Select Tabs");

    verticalLayout = new QVBoxLayout(this);
    this->setLayout(verticalLayout);

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
                }else{
                    selectedViews.removeOne(view); // will return false if not there
                }
            });

            // TODO :
                // give a option to show only recently active tabs
                // Restricted to max 4 selections
        }
    }

    scrollArea->setWidget(gridContainer);
    scrollArea->setWidgetResizable(true);
    verticalLayout->addWidget(scrollArea);

    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    verticalLayout->addWidget(buttonBox);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
}

TabSelectionDialog::~TabSelectionDialog()
{
    // delete ui;
}

QVector<WebEngineView*> TabSelectionDialog::getSelectedViews(){
    return selectedViews;
}
