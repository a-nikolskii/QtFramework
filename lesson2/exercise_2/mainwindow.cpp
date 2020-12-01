#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

//QStringList Languages = {"C++", "C#", "Java", "PHP", "Python"};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QStringList Languages = {"C++", "C#", "Java", "PHP", "Python"};

    m_model = new QStandardItemModel(Languages.size(), 1, this);
    for (int row = 0; row < m_model->rowCount(); ++row){
        QModelIndex index = m_model->index(row, 0);
        m_model->setData(index, Languages[row], Qt::DisplayRole);
        m_model->setData(index, "Tooltip for " + Languages[row], Qt::ToolTipRole);
        m_model->setData(index, QIcon("../exercise_2/image/"+ Languages[row] + ".png"), Qt::DecorationRole);
    }

    ui->checkBox->setChecked(true);
    ui->listView->setViewMode(QListView::IconMode);
    ui->listView->setModel(m_model);

    connect(ui->listView, SIGNAL(clicked(QModelIndex)), this, SLOT(listChanedSlot(QModelIndex)));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QStandardItem* newItem = new QStandardItem(QIcon("../exercise_2/image/default.png"), "NewItem");
    newItem->setData("Tooltip for default", Qt::ToolTipRole);

    m_model->appendRow(newItem);
}

void MainWindow::on_pushButton_2_clicked()
{
    if (ui->listView->currentIndex().isValid()){
        m_model->removeRow(ui->listView->currentIndex().row());
    }
    else {
        if(m_model->rowCount() > 0){
            QMessageBox::information(this, "Error", "Select item to remove");
        }
        else {
            QMessageBox::information(this, "Error", "List is empty");
        }
    }
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    if(ui->checkBox->isChecked()) {
        ui->listView->setViewMode(QListView::IconMode);
    }
    else {
        ui->listView->setViewMode(QListView::ListMode);
    }
}

