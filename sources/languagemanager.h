#ifndef LANGUAGEMANAGER_H
#define LANGUAGEMANAGER_H

#include <QTranslator>
#include <QLocale>
#include <QActionGroup>

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
private:
    static LanguageManager* p_instance;
    static LanguageManagerDestroyer destroyer;
    QTranslator m_translator;
    QString m_curLang = "en";
protected:
    LanguageManager() { }
    LanguageManager( const LanguageManager& );
    LanguageManager& operator=( LanguageManager& );
    ~LanguageManager() { }
    friend class LanguageManagerDestroyer;
public:
    static LanguageManager& get_instance();
    void loadLanguage( const QString& langCode );
    void SwitchTranslator( const QString& langCode );
    QString getCurLang() { return m_curLang; }
};


#endif // LANGUAGEMANAGER_H
