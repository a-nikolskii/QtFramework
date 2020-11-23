#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "QDoubleValidator"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_calculate_clicked();

    void on_pushButton_clear_clicked();

    void on_edited();

    void on_radioButton_d_clicked();

    void on_radioButton_r_clicked();

private:
    Ui::MainWindow *ui;
    QDoubleValidator m_side_validator;
    QDoubleValidator m_degree_validator;
    QDoubleValidator m_radian_validator;

};

#endif // MAINWINDOW_H
