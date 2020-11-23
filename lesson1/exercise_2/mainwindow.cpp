#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <unordered_map>
#include "QtMath"
#include "unordered_set"
#include "QTimer"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_side_validator(0, 1000, 10, this)
    , m_degree_validator(0, 180, 10, this)
    , m_radian_validator(0, 3.1415926535, 10, this)
{
    ui->setupUi(this);

    std::unordered_set<QDoubleValidator*> s {
        &m_side_validator,
        &m_degree_validator,
        &m_radian_validator,
    };
    for (auto valid : s) {
        valid->setNotation(QDoubleValidator::StandardNotation);
    }

    std::unordered_map<QLineEdit*, QDoubleValidator&> m {
        {ui->lineEdit_a, m_side_validator},
        {ui->lineEdit_b, m_side_validator},
        {ui->lineEdit_angle, m_radian_validator}, //by default
    };
    for (auto pair : m){
        pair.first->setValidator(&pair.second);
        connect(pair.first, SIGNAL(textEdited(QString)), this, SLOT(on_edited()));
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_calculate_clicked()
{
    ui->label_result->clear();

    double side_a, side_b, angle, side_c;
    std::unordered_map<QLineEdit*, double&> m {
        {ui->lineEdit_a, side_a},
        {ui->lineEdit_b, side_b},
        {ui->lineEdit_angle, angle},
    };

    QString message_specify("please specify ");
    for (auto pair : m) {
        if (pair.first->text().isEmpty()){
            message_specify += pair.first->objectName() + ", ";
            continue;
        }
        pair.second = pair.first->text().toDouble();
    }

    if (message_specify != "please specify ") {
        message_specify.chop(2);
        ui->label_result->setText(message_specify);
        return;
    }

    //Следующие два if нужны потому, что QDoubleValidator отрабатывает своебразно
    //и по факту он помогает только от ввода букв и непривильных символов.
    //в гуле удалось найти такое предложение перегрузки QValidator::State validate(QString & s, int & pos) const
    //https://stackoverrun.com/ru/q/9697952
    //Но чего то оно тоже не особо помогло. Поэтому решил сильно не заморачиваться и просто в коде проверить.
    if (ui->radioButton_d->isChecked() && (angle <=0 || angle >=180 )){
        ui->label_result->setText("Wrong value. Angle has to be in range (0, 180)");
        return;
    }

    if (ui->radioButton_r->isChecked() && (angle <=0 || angle >= M_PI)) {
        ui->label_result->setText("Wrong value. Angle has to be in range (0, pi)");
        return;
    }

    if (ui->radioButton_d->isChecked()) {
        angle = qDegreesToRadians(angle);
    }

    side_c = sqrt(pow(side_a,2) + pow(side_b,2) - side_a * side_b * qCos(angle));

    ui->label_result->setText("side c  =  " + QString::number(side_c));

}


void MainWindow::on_pushButton_clear_clicked()
{
    ui->label_result->clear();
    ui->radioButton_r->setChecked(true);

    std::vector<QLineEdit*> v {
        ui->lineEdit_a,
        ui->lineEdit_b,
        ui->lineEdit_angle,
    };

    for (auto line : v) {
        line->clear();
    }

    QTimer::singleShot(0, ui->lineEdit_a, SLOT(setFocus()));

}


void MainWindow::on_edited(){};


void MainWindow::on_radioButton_d_clicked()
{
    ui->lineEdit_angle->setValidator(&m_degree_validator);
    QTimer::singleShot(0, ui->lineEdit_angle, SLOT(setFocus()));
}


void MainWindow::on_radioButton_r_clicked()
{
    ui->lineEdit_angle->setValidator(&m_radian_validator);
    QTimer::singleShot(0, ui->lineEdit_angle, SLOT(setFocus()));

}
