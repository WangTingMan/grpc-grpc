#pragma once
#include <memory>
#include <mutex>
#include <string>
#include <thread>

#include "server_streaming_rpc.grpc.pb.h"

#include <grpcpp/server_builder.h>
#include <grpcpp/server.h>

#include "greeter_ext_client_proxy.h"

enum class ServiceRunningStatus : uint8_t
{
  stopped,
  starting,
  started,
  stopping
};

class GreeterExtService
{

public:

  GreeterExtService();

  void StartOn( std::string a_endpoint );

  bool IsBidirectionConnected()
  {
    for( auto& ele : m_client_proxies )
    {
      if( ele->IsBidirectionConnected() )
      {
        return true;
      }
    }
    return false;
  }

  void SendBiDirectionStreamingServiceMessage( std::string a_msg )
  {
    for( auto& ele : m_client_proxies )
    {
      helloworld::MessageFromServer msg;
      msg.set_msg( a_msg );
      msg.set_id( m_msg_id++ );
      if( ele->IsBidirectionConnected() )
      {
        ele->AsyncSendBidDirectionMessage( msg );
      }
    }
  }

private:

  void loop();

  std::recursive_mutex m_mutex;
  ServiceRunningStatus m_running_status;

  std::thread m_loop_thread;
  helloworld::HelloService::AsyncService m_detail_service;
  grpc::ServerBuilder m_service_builder;
  std::unique_ptr<grpc::ServerCompletionQueue> m_server_task_queue;
  std::unique_ptr<grpc::Server> m_rpc_server;
  std::vector<std::shared_ptr<GreeterExtClientProxy>> m_client_proxies;
  int m_msg_id = 0;
};

