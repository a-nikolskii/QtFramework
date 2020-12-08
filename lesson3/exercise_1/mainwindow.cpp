#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    filter = trUtf8("Текстовый файл(*.txt)");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_save_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this, "Сохранение файла", QDir::currentPath(), filter);

    if (filename.size() > 0) {

        QFile file(filename);

        if (file.open(QFile::WriteOnly | QFile::NewOnly)) {
            QTextStream stream(&file);
            stream << ui->plainTextEdit->toPlainText();
            file.close();
        }
    }
}

void MainWindow::on_pushButton_open_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this, "Открытие файла", QDir::currentPath(), filter);

    if (filename.size() > 0) {

        QFile file(filename);

        if (file.open(QFile::ReadOnly | QFile::ExistingOnly)) {
            QTextStream stream(&file);
            ui->plainTextEdit->setPlainText(stream.readAll());
            file.close();

        }
    }
}
