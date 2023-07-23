#include "greeter_ext_client_proxy.h"
#include "tag_handler_manager.h"

#include "tag_handler_manager.h"

#include <iostream>

void BidirectionalStreamMessagesControlBlock::start()
{
  if( m_start_id != 0 || m_done_id != 0 )
  {
    return;
  }

  std::function<void( bool )> fun;
  fun = std::bind( &BidirectionalStreamMessagesControlBlock::HandleRequestHelloDone,
    shared_from_this(), std::placeholders::_1 );
  uint64_t id = TagHandlerManager::get_instance().register_tag_handler( fun );
  m_done_id = id;
  m_serverContext.AsyncNotifyWhenDone( ( void* )( id ) );

  fun = std::bind( &BidirectionalStreamMessagesControlBlock::HandleRequstHelloStart,
    shared_from_this(), std::placeholders::_1 );
  id = TagHandlerManager::get_instance().register_tag_handler( fun );
  m_start_id = id;
  m_detail_service.RequestBidirectionalStreamMessages( &m_serverContext, &m_biddiraction_stream,
    m_server_task_queue, m_server_task_queue, ( void* )( id ) );
}

void BidirectionalStreamMessagesControlBlock::HandleRequestHelloDone( bool ok )
{
  if( !ok )
  {
    return;
  }

  // this RPC invoking done.
}

void BidirectionalStreamMessagesControlBlock::HandleRequstHelloStart( bool ok )
{
  if( m_read_come_id == 0 )
  {
    std::function<void( bool )> fun;
    fun = std::bind( &BidirectionalStreamMessagesControlBlock::HandleRequestHelloMessageReadCome,
      shared_from_this(), std::placeholders::_1 );
    uint64_t id = TagHandlerManager::get_instance().register_tag_handler( fun );
    m_read_come_id = id;
  }
  m_started = true;
  m_biddiraction_stream.Read( &m_read_msg, ( void* )( m_read_come_id ) );
}

void BidirectionalStreamMessagesControlBlock::HandleRequestHelloMessageReadCome( bool ok )
{

  if( m_read_come_id == 0 )
  {
    std::function<void( bool )> fun;
    fun = std::bind( &BidirectionalStreamMessagesControlBlock::HandleRequestHelloMessageReadCome,
      shared_from_this(), std::placeholders::_1 );
    uint64_t id = TagHandlerManager::get_instance().register_tag_handler( fun );
    m_read_come_id = id;
  }

  // Came message can use: m_read_msg
  // To do more reading.
  std::cout << "Message from client: id = " << m_read_msg.id()
    << ", message = " << m_read_msg.msg() << std::endl;
  m_biddiraction_stream.Read( &m_read_msg, ( void* )( m_read_come_id ) );
}

void BidirectionalStreamMessagesControlBlock::UnregisterAllTagHandlers()
{
  TagHandlerManager::get_instance().delete_tag_handler( m_read_come_id );
  TagHandlerManager::get_instance().delete_tag_handler( m_done_id );
  TagHandlerManager::get_instance().delete_tag_handler( m_start_id );
  TagHandlerManager::get_instance().delete_tag_handler( m_write_done_id );
  m_read_come_id = 0;
  m_done_id = 0;
  m_start_id = 0;
  m_write_done_id = 0;
}

void BidirectionalStreamMessagesControlBlock::AsyncSendBidDirectionMessage( helloworld::MessageFromServer a_msg )
{
  if( !m_message_sending )
  {
    if( m_write_done_id == 0 )
    {
      std::function<void( bool )> fun;
      fun = std::bind( &BidirectionalStreamMessagesControlBlock::HandleMessageWriteDone,
        shared_from_this(), std::placeholders::_1 );
      uint64_t id = TagHandlerManager::get_instance().register_tag_handler( fun );
      m_write_done_id = id;
    }

    m_biddiraction_stream.Write( std::move( a_msg ), ( void* )( m_write_done_id ) );
    m_message_sending = true;
  }
  else
  {
    m_msg_to_send.push_back( a_msg );
  }
}

void BidirectionalStreamMessagesControlBlock::HandleMessageWriteDone( bool ok )
{
  m_message_sending = false;
  if( m_msg_to_send.empty() )
  {
    return;
  }

  AsyncSendBidDirectionMessage( m_msg_to_send.front() );
  m_msg_to_send.erase( m_msg_to_send.begin() );
}

GreeterExtClientProxy::GreeterExtClientProxy
  (
  helloworld::HelloService::AsyncService& a_detail_service,
  grpc::ServerCompletionQueue* a_server_task_queue
  )
  : m_detail_service{ a_detail_service }
  , m_server_task_queue{ a_server_task_queue }
{

}

GreeterExtClientProxy::~GreeterExtClientProxy()
{
  UnregisterAllTagHandlers();
}

void GreeterExtClientProxy::start()
{
  if( !m_bidiractionalStreamCb )
  {
    m_bidiractionalStreamCb = std::make_shared<BidirectionalStreamMessagesControlBlock>( m_detail_service );
    m_bidiractionalStreamCb->m_server_task_queue = m_server_task_queue;
  }
  m_bidiractionalStreamCb->start();
}

void GreeterExtClientProxy::UnregisterAllTagHandlers()
{
  for( auto ele : m_registered_tag_ids )
  {
    TagHandlerManager::get_instance().delete_tag_handler( ele );
  }
  m_registered_tag_ids.clear();

  if( m_bidiractionalStreamCb )
  {
    m_bidiractionalStreamCb->UnregisterAllTagHandlers();
  }
}


