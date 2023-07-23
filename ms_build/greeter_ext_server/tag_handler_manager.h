#pragma once
#include <functional>
#include <map>
#include <mutex>

class TagHandlerManager
{

public:

  static TagHandlerManager& get_instance();

  uint64_t register_tag_handler( std::function<void( bool )> a_handler );

  std::function<void( bool )> find_tag_handler( uint64_t ) const;

  void delete_tag_handler( uint64_t );

private:

  TagHandlerManager() {};

  mutable std::recursive_mutex m_mutex;
  std::map<uint64_t, std::function<void( bool )>> m_registered_handler;
  uint64_t m_current_index = 0;
};

