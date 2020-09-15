#ifndef LANGUAGEMANAGER_H
#define LANGUAGEMANAGER_H

#include <QTranslator>

class LanguageManager;

class LanguageManagerDestroyer
{
private:
    LanguageManager* p_instance;
public:
    ~LanguageManagerDestroyer();
    void initialize( LanguageManager* p );
};

class LanguageManager
{
public:
    static LanguageManager& get_instance();
    void loadLanguage( const QString& langCode );
    void SwitchTranslator( const QString& langCode );
    QString getCurLang() { return m_curLang; }
protected:
    LanguageManager() { }
    LanguageManager( const LanguageManager& );
    LanguageManager& operator=( LanguageManager& );
    ~LanguageManager() { }
    friend class LanguageManagerDestroyer;
private:
    static LanguageManager* p_instance;
    static LanguageManagerDestroyer destroyer;
    QTranslator m_translator;
    QString m_curLang = "en";
};

#endif // LANGUAGEMANAGER_H
