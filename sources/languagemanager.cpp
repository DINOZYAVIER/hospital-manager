#include "precompiled.h"
#include "languagemanager.h"

LanguageManager * LanguageManager::p_instance = 0;
LanguageManagerDestroyer LanguageManager::destroyer;

LanguageManagerDestroyer::~LanguageManagerDestroyer()
{
    delete p_instance;
}

void LanguageManagerDestroyer::initialize( LanguageManager* p )
{
    p_instance = p;
}

LanguageManager& LanguageManager::get_instance()
{
    if( !p_instance )
    {
        p_instance = new LanguageManager();
        destroyer.initialize( p_instance );
    }
    return *p_instance;
}

void LanguageManager::loadLanguage( const QString& langCode )
{
    if( langCode == "en" )
        qApp->removeTranslator( &m_translator );
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

