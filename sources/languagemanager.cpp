#include "precompiled.h"
#include "languagemanager.h"

LanguageManager * LanguageManager::p_instance = 0;

LanguageManager& LanguageManager::get_instance()
{
    static LanguageManager *p_instance = new LanguageManager();
    return *p_instance;
}

void LanguageManager::loadLanguage( const QString& langCode )
{
    if( langCode == "en" )
    {
        qApp->removeTranslator( &m_translator );
        m_curLang = "en";
    }
    else
    {
        if( m_curLang != langCode )
        {
            m_curLang = langCode;
            SwitchTranslator( langCode );
        }
    }
}

void LanguageManager::SwitchTranslator( const QString& langCode )
{
    // remove the old translator
     qApp->removeTranslator( &m_translator );

     // load the new translator
     if( m_translator.load( ":/translations/hospital_" + langCode + ".qm" ))
         qApp->installTranslator( &m_translator );
}

