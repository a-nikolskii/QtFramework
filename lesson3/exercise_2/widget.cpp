#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout* mainLayout = new QVBoxLayout;
    m_buttonGroup = new QGroupBox(tr("Operations:"));
    m_infoGroupBox = new QGroupBox(tr("Information:"));
    m_textEdit = new QPlainTextEdit;


    mainLayout->addWidget(m_textEdit);
    mainLayout->addWidget(m_buttonGroup);
    mainLayout->addWidget(m_infoGroupBox);
    this->setLayout(mainLayout);



    QHBoxLayout* butLayout = new QHBoxLayout;
    m_choiseButton = new QPushButton(tr("Choose file"));
    m_getButton = new QPushButton(tr("Get rate"));
    m_getButton->setEnabled(false);
    butLayout->addWidget(m_choiseButton);
    butLayout->addWidget(m_getButton);
    m_buttonGroup->setLayout(butLayout);




    QFormLayout* infoLayout = new QFormLayout;
    m_usdLineEdit = new QLineEdit;
    m_eurLineEdit = new QLineEdit;
    infoLayout->addRow(new QLabel(tr("USD")), m_usdLineEdit);
    infoLayout->addRow(new QLabel(tr("EUR")), m_eurLineEdit);
    m_infoGroupBox->setLayout(infoLayout);

    connect(m_choiseButton, SIGNAL(clicked()), this, SLOT(on_m_choiseButton_cliked()));
    connect(m_getButton, SIGNAL(clicked()), this, SLOT(on_m_getButton_cliked()));

    m_oldStr = nullptr;

}


Widget::~Widget()
{
    delete m_oldStr;
}


void Widget::on_m_choiseButton_cliked(){
    QString filename =
    QFileDialog::getOpenFileName(this, tr("Open file"),QDir::currentPath(), "Html(*.html);;ALL(*.*)");

    if (filename.isEmpty()) {
        qDebug() << "Filename is empty";
        return;
    }

    else{
        qDebug() << "Chosen file: " << filename;

        QFile in_file(filename);

        if (!in_file.open(QIODevice::ReadOnly)){
            m_textEdit->setPlainText("");
            m_getButton->setEnabled(false);
            m_usdLineEdit->setText("");
            m_eurLineEdit->setText("");
            QMessageBox::information(this, "Error", filename + " is not open");
        }

        else {
            QTextStream stream(&in_file);
            QString* str = new QString(stream.read(in_file.size()));
            m_textEdit->setPlainText(*str);
            if (m_oldStr){
                delete m_oldStr;
            }
            m_oldStr = str;

            m_getButton->setEnabled(true);

        }
    }

}


void Widget::on_m_getButton_cliked(){
    QStringList list;
    QRegExp regex("(<div class=\"rate__currency svelte-1lhokyh\">)([+-]?([0-9]*[.])?[0-9]+)(</div>)");
    int lastPos = 0;
    while ((lastPos = regex.indexIn(*m_oldStr, lastPos)) != -1) {
        lastPos += regex.matchedLength();
        list.append(regex.cap(2));
    }
    m_usdLineEdit->setText(list[0]);
    m_eurLineEdit->setText(list[1]);

}
