#include "tag_handler_manager.h"

TagHandlerManager& TagHandlerManager::get_instance()
{
  static TagHandlerManager instance;
  return instance;
}

uint64_t TagHandlerManager::register_tag_handler( std::function<void( bool )> a_handler )
{
  std::lock_guard<std::recursive_mutex> locker( m_mutex );
  uint64_t ret = m_current_index++;
  m_registered_handler[ret] = a_handler;
  return ret;
}

std::function<void( bool )> TagHandlerManager::find_tag_handler( uint64_t a_tag_id ) const
{
  std::lock_guard<std::recursive_mutex> locker( m_mutex );
  std::function<void( bool )> fun;
  auto it = m_registered_handler.find( a_tag_id );
  if( it != m_registered_handler.end() )
  {
    fun = it->second;
  }
  return fun;
}

void TagHandlerManager::delete_tag_handler( uint64_t a_tag_id )
{
  std::lock_guard<std::recursive_mutex> locker( m_mutex );
  m_registered_handler.erase( a_tag_id );
}

