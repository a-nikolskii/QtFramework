#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_add_clicked()
{
    QString text_from;
    QString text_to;

    text_from = ui->plainTextEdit_from->toPlainText();
    text_to = ui->textEdit_to->toPlainText();
    ui->textEdit_to->setPlainText(text_to + text_from);

}

void MainWindow::on_pushButton_replace_clicked()
{
    QString text_from;

    ui->textEdit_to->clear();

    text_from = ui->plainTextEdit_from->toPlainText();

    ui->textEdit_to->setPlainText(text_from);

}

void MainWindow::on_pushButton_random_clicked()
{
    QString html_string("<font color='red'>Hello</font>");

    ui->textEdit_to->clear();
    ui->textEdit_to->setHtml(html_string);
}

