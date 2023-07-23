#include "greeter_ext_service.h"
#include "tag_handler_manager.h"

GreeterExtService::GreeterExtService()
  : m_running_status{ ServiceRunningStatus::stopped }
{

}

void GreeterExtService::StartOn( std::string a_endpoint )
{
  std::lock_guard<std::recursive_mutex> lcker( m_mutex );
  if( m_running_status != ServiceRunningStatus::stopped )
  {
    // We should start this service if it is stopped.
    return;
  }

  m_running_status = ServiceRunningStatus::starting;

  m_service_builder.AddListeningPort( a_endpoint, grpc::InsecureServerCredentials() );
  m_service_builder.RegisterService( &m_detail_service );
  m_server_task_queue = m_service_builder.AddCompletionQueue();
  m_rpc_server = m_service_builder.BuildAndStart();
  if( !m_rpc_server )
  {
    // Build and start failed.
    return;
  }

  std::shared_ptr<GreeterExtClientProxy> proxy;
  proxy = std::make_shared<GreeterExtClientProxy>( m_detail_service, m_server_task_queue.get() );
  m_client_proxies.push_back( proxy );
  proxy->start();

  if( m_loop_thread.joinable() )
  {
    return;
  }

  m_loop_thread = std::thread(&GreeterExtService::loop, this);

}

void GreeterExtService::loop()
{
  while( true )
  {
    void* tag = nullptr;
    bool ok = false;
    bool ret = m_server_task_queue->Next( &tag, &ok );
    if( ret )
    {
      uint64_t id = uint64_t(tag);
      auto fun = TagHandlerManager::get_instance().find_tag_handler( id );
      if( fun )
      {
        fun( ok );
      }
      else
      {
        std::cout << "No such Tag handler!\n";
      }
    }
  }
}

