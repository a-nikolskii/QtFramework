#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QtMath"
#include "quadraticequation.h"
#include "unordered_map"
#include "QTimer"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_validator(1000, 1000, 10, this)
{
    ui->setupUi(this);


    m_validator.setNotation(QDoubleValidator::StandardNotation);
    std::vector<QLineEdit*> v = {
        ui->lineEdit_a,
        ui->lineEdit_b,
        ui->lineEdit_c
    };
    for (auto line : v){
        line->setValidator(&m_validator);
        connect(line, SIGNAL(textEdited(QString)), this, SLOT(on_edited()));
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_edited(){};

void MainWindow::on_pushButton_clicked()
{
    ui->label_result->clear();

    double a, b, c;

    std::unordered_map<QLineEdit*, double&> m = {
        {ui->lineEdit_a, a},
        {ui->lineEdit_b, b},
        {ui->lineEdit_c, c}};

    QString message_specify("please specify ");
    for (auto var : m) {
        if (var.first->text().isEmpty()) {
            message_specify += " " + var.first->objectName() + ", ";
            continue;
        }
        var.second = QLocale::system().toDouble(var.first->text());

    }


    if (message_specify != "please specify ") {
        message_specify.chop(2);
        ui->label_result->setText(message_specify);
        return;
    }



    QuadraticEquation equation(a, b, c);

    if (equation.rootCount() == WRONG_SPECIFIE) {
        ui->label_result->setText("Wrong coefficient specifie");
    }

    else if (equation.rootCount() == NO_REAL_ROOT) {
        ui->label_result->setText("Equation doesn`t have real roots");
    }

    else if (equation.rootCount() == ONE_REAL_ROOT) {
        ui->label_result->setText("x = " + QString::number(equation.getRoot().front()));
    }

    else if (equation.rootCount() == TWO_REAL_ROOT) {
        ui->label_result->setText("x1 =  " + QString::number(equation.getRoot().front()) + " \n" +
                                  "x2 =  " + QString::number(equation.getRoot().back()));
    }


}


void MainWindow::on_pushButton_2_clicked()
{
    std::vector<QLineEdit*> v = {
        ui->lineEdit_a,
        ui->lineEdit_b,
        ui->lineEdit_c,
    };
    for (auto line : v) {
        line->clear();
    }

    ui->label_result->clear();

    QTimer::singleShot(0, ui->lineEdit_a, SLOT(setFocus()));
}
