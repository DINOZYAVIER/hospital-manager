#ifndef LANGUAGEMANAGER_H
#define LANGUAGEMANAGER_H

#include <QTranslator>

class LanguageManager
{
public:
    static LanguageManager& instance();
    void loadLanguage( const QString& langCode );
    void SwitchTranslator( const QString& langCode );
    QString CurLang() { return m_curLang; }
    ~LanguageManager() { delete p_instance; }
private:
    static LanguageManager* p_instance;
    QTranslator m_translator;
    QString m_curLang = "en";
};

#endif // LANGUAGEMANAGER_H
