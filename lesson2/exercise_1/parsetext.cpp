#include "parsetext.h"
#include <algorithm>
#include <iostream>



QMap<QString, QString> ParseText::s_map = {
    {"rub", QChar(0x20BD)},
    {"eur", QChar(0x20AC)},
    {"cpm", QChar(0x00A9)},
    {"ppm", QChar(0x2030)},
};


ParseText::ParseText() : m_text(""),
                         m_preText(""),
                         m_pos(0) 
{};

bool ParseText::change(const QString& input_str){
    qint32 lenght = std::min<qint32>(m_pos, std::min<qint32>(m_text.length(), input_str.length()));
    m_preText = "";
    

    for (qint32 i= 0; i < lenght; ++i) {
        if (m_text[i] != input_str[i]) {
           m_pos = i;
           break;
        }
    } 

    if (m_pos > lenght){ //если этого не сделать, то при вводе вида "@rub@#@kdjf@" будем получать неправильную работу
        m_pos = lenght;  //это связано с тем, что верхний цикл не выполнится ни разу и m_pos будет указывать не в то место.
    }
    
    const QChar* arStr = input_str.constData();
    
    qint32 lastp = -1;
    qint32 ppos = 0;
    bool change = false;

    for (qint32 fnd = input_str.indexOf("#@", m_pos);
         fnd != -1 && lastp != m_pos;
         fnd = input_str.indexOf("#@", m_pos)){
        m_preText.insert(m_preText.length(), &arStr[ppos], fnd);
        lastp = m_pos;
        m_pos = fnd;
        
        int end_char = input_str.indexOf("@", fnd + 2);
        int space = input_str.indexOf(" ", fnd);
        
        if((end_char < space || space == -1) && end_char != -1) {
            QString spec_symbol;
            spec_symbol.insert(0, &arStr[fnd + 2], end_char - fnd - 2);
            m_preText += getSpecSymbol(spec_symbol);
            m_pos = end_char + 1;
            change = true;
        }

        m_preText.insert(m_preText.length(), &arStr[m_pos], input_str.length() - m_pos);
    }
    return change;
}


QString ParseText::getSpecSymbol(const QString& key) const {
    if (s_map.contains(key.toLower())) {
        return s_map.value(key.toLower());
    }
    else {
        std::cerr << "Key \"" << key.toStdString() << "\" not found in s_map" << std::endl;
        return "#@" + key + "@";
    }
}


QString ParseText::getText(){
    m_text = m_preText;
    return m_text;
}
