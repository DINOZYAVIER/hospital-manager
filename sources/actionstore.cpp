#include "actionstore.h"

void ActionStore::addAction( ActionID id, QAction * action )
{
    m_actions.insert( id, action );
    //m_actions[ id ] = action;
}

QAction* ActionStore::action( ActionID id ) const
{
   Q_ASSERT( m_actions.contains( id ) );
   return m_actions.value( id );
}

