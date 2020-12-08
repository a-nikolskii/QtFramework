#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QFormLayout>
#include <QPlainTextEdit>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QFileDialog>
#include <QDebug>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QStringList>
#include <QRegExp>


class Widget : public QWidget
{
    Q_OBJECT

private:
    QPlainTextEdit* m_textEdit;
    QGroupBox* m_buttonGroup;
    QGroupBox* m_infoGroupBox;
    QPushButton* m_choiseButton;
    QPushButton* m_getButton;
    QLineEdit* m_usdLineEdit;
    QLineEdit* m_eurLineEdit;
    QString* m_oldStr;


public:
    Widget(QWidget *parent = nullptr);
    ~Widget(); 


private slots:

    void on_m_choiseButton_cliked();

    void on_m_getButton_cliked();
};
#endif // WIDGET_H
