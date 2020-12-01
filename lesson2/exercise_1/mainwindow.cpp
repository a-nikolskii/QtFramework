#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    parseText = new(std::nothrow) ParseText;
    if (parseText == nullptr) {
        std::cerr << "Can't allocate memory parseText" << std::endl;
        close();
    }

    //ui->plainTextEdit->setPlainText(parseText->getSpecSymbol("eur"));
}

MainWindow::~MainWindow()
{
    delete ui;
    if (parseText){
        delete parseText;
        parseText = nullptr;
    }
}


void MainWindow::on_plainTextEdit_textChanged()
{
    QString str = ui->plainTextEdit->toPlainText();

    QTextCursor cursor = ui->plainTextEdit->textCursor();
    if (parseText->change(str)){
        ui->plainTextEdit->setPlainText(parseText->getText());
        ui->plainTextEdit->setTextCursor(cursor);
    }
}
