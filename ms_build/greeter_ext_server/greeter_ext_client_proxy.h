#pragma once

#include "server_streaming_rpc.grpc.pb.h"

#include <grpcpp/server.h>

#include <atomic>
#include <memory>
#include <vector>

struct BidirectionalStreamMessagesControlBlock : public std::enable_shared_from_this<BidirectionalStreamMessagesControlBlock>
{
  BidirectionalStreamMessagesControlBlock( helloworld::HelloService::AsyncService& a_service )
    : m_biddiraction_stream( &m_serverContext )
    , m_detail_service( a_service )
  {

  }

  void start();

  void HandleRequestHelloDone( bool ok );

  void HandleRequstHelloStart( bool ok );

  void HandleRequestHelloMessageReadCome( bool ok );

  void HandleMessageWriteDone( bool ok );

  void UnregisterAllTagHandlers();

  void AsyncSendBidDirectionMessage( helloworld::MessageFromServer a_msg );

  bool IsBidirectionConnected()
  {
    return m_started;
  }

  grpc::ServerContext m_serverContext;
  grpc::ServerAsyncReaderWriter<helloworld::MessageFromServer, helloworld::MessageFromClient> m_biddiraction_stream;
  helloworld::HelloService::AsyncService& m_detail_service;
  grpc::ServerCompletionQueue* m_server_task_queue = nullptr;

  std::vector<helloworld::MessageFromServer> m_msg_to_send;
  helloworld::MessageFromClient m_read_msg;
  uint64_t m_read_come_id = 0;
  uint64_t m_done_id = 0;
  uint64_t m_start_id = 0;
  uint64_t m_write_done_id = 0;
  bool m_started = false;
  std::atomic_bool m_message_sending = false;
};

class GreeterExtClientProxy : public std::enable_shared_from_this<GreeterExtClientProxy>
{

public:

  GreeterExtClientProxy
    (
    helloworld::HelloService::AsyncService& a_detail_service,
    grpc::ServerCompletionQueue* a_server_task_queue
    );

  void start();

  ~GreeterExtClientProxy();

  void UnregisterAllTagHandlers();

  void AsyncSendBidDirectionMessage( helloworld::MessageFromServer a_msg )
  {
    if( m_bidiractionalStreamCb )
    {
      m_bidiractionalStreamCb->AsyncSendBidDirectionMessage( a_msg );
    }
  }

  bool IsBidirectionConnected()
  {
    return m_bidiractionalStreamCb->IsBidirectionConnected();
  }

private:

  helloworld::HelloService::AsyncService& m_detail_service;
  grpc::ServerCompletionQueue* m_server_task_queue;
  std::vector<uint64_t> m_registered_tag_ids;
  std::shared_ptr<BidirectionalStreamMessagesControlBlock> m_bidiractionalStreamCb;
};


