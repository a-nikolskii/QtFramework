#ifndef PARSETEXT_H
#define PARSETEXT_H

#include <QString>
#include <QMap>

const QChar RUB (0x20BD);
const QChar EUR (0x20AC);
const QChar CPM (0x00A9);
const QChar PPM (0x2030);

class ParseText
{
private:
    QString m_text;
    QString m_preText;
    int m_pos;
    static QMap<QString, QString> s_map;

public:
    ParseText();
    bool change(const QString& input_str);
    QString getText();
    QString getSpecSymbol(const QString& key) const;
};


#endif // PARSETEXT_H
