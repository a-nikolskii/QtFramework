#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDoubleValidator>

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
    void on_pushButton_clicked();

    void on_lineEdit_a_textEdited(const QString &arg1);

    void on_edited();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    QDoubleValidator m_validator;
};

#endif // MAINWINDOW_H
