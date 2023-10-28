// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: server_streaming_rpc.proto

#include "server_streaming_rpc.pb.h"
#include "server_streaming_rpc.grpc.pb.h"

#include <functional>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/channel_interface.h>
#include <grpcpp/impl/codegen/client_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/method_handler_impl.h>
#include <grpcpp/impl/codegen/rpc_service_method.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/sync_stream.h>
namespace helloworld {

static const char* HelloService_method_names[] = {
  "/helloworld.HelloService/SayHello",
  "/helloworld.HelloService/ClientStreamMessages",
  "/helloworld.HelloService/ServerStreamMessages",
  "/helloworld.HelloService/BidirectionalStreamMessages",
};

std::unique_ptr< HelloService::Stub> HelloService::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  (void)options;
  std::unique_ptr< HelloService::Stub> stub(new HelloService::Stub(channel));
  return stub;
}

HelloService::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel)
  : channel_(channel), rpcmethod_SayHello_(HelloService_method_names[0], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_ClientStreamMessages_(HelloService_method_names[1], ::grpc::internal::RpcMethod::CLIENT_STREAMING, channel)
  , rpcmethod_ServerStreamMessages_(HelloService_method_names[2], ::grpc::internal::RpcMethod::SERVER_STREAMING, channel)
  , rpcmethod_BidirectionalStreamMessages_(HelloService_method_names[3], ::grpc::internal::RpcMethod::BIDI_STREAMING, channel)
  {}

::grpc::Status HelloService::Stub::SayHello(::grpc::ClientContext* context, const ::helloworld::HelloRequest& request, ::helloworld::HelloReply* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_SayHello_, context, request, response);
}

void HelloService::Stub::experimental_async::SayHello(::grpc::ClientContext* context, const ::helloworld::HelloRequest* request, ::helloworld::HelloReply* response, std::function<void(::grpc::Status)> f) {
  return ::grpc::internal::CallbackUnaryCall(stub_->channel_.get(), stub_->rpcmethod_SayHello_, context, request, response, std::move(f));
}

::grpc::ClientAsyncResponseReader< ::helloworld::HelloReply>* HelloService::Stub::AsyncSayHelloRaw(::grpc::ClientContext* context, const ::helloworld::HelloRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::helloworld::HelloReply>::Create(channel_.get(), cq, rpcmethod_SayHello_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::helloworld::HelloReply>* HelloService::Stub::PrepareAsyncSayHelloRaw(::grpc::ClientContext* context, const ::helloworld::HelloRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::helloworld::HelloReply>::Create(channel_.get(), cq, rpcmethod_SayHello_, context, request, false);
}

::grpc::ClientWriter< ::helloworld::MessageFromClient>* HelloService::Stub::ClientStreamMessagesRaw(::grpc::ClientContext* context, ::helloworld::MessageFromServer* response) {
  return ::grpc::internal::ClientWriterFactory< ::helloworld::MessageFromClient>::Create(channel_.get(), rpcmethod_ClientStreamMessages_, context, response);
}

::grpc::ClientAsyncWriter< ::helloworld::MessageFromClient>* HelloService::Stub::AsyncClientStreamMessagesRaw(::grpc::ClientContext* context, ::helloworld::MessageFromServer* response, ::grpc::CompletionQueue* cq, void* tag) {
  return ::grpc::internal::ClientAsyncWriterFactory< ::helloworld::MessageFromClient>::Create(channel_.get(), cq, rpcmethod_ClientStreamMessages_, context, response, true, tag);
}

::grpc::ClientAsyncWriter< ::helloworld::MessageFromClient>* HelloService::Stub::PrepareAsyncClientStreamMessagesRaw(::grpc::ClientContext* context, ::helloworld::MessageFromServer* response, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncWriterFactory< ::helloworld::MessageFromClient>::Create(channel_.get(), cq, rpcmethod_ClientStreamMessages_, context, response, false, nullptr);
}

::grpc::ClientReader< ::helloworld::MessageFromServer>* HelloService::Stub::ServerStreamMessagesRaw(::grpc::ClientContext* context, const ::helloworld::MessageFromClient& request) {
  return ::grpc::internal::ClientReaderFactory< ::helloworld::MessageFromServer>::Create(channel_.get(), rpcmethod_ServerStreamMessages_, context, request);
}

::grpc::ClientAsyncReader< ::helloworld::MessageFromServer>* HelloService::Stub::AsyncServerStreamMessagesRaw(::grpc::ClientContext* context, const ::helloworld::MessageFromClient& request, ::grpc::CompletionQueue* cq, void* tag) {
  return ::grpc::internal::ClientAsyncReaderFactory< ::helloworld::MessageFromServer>::Create(channel_.get(), cq, rpcmethod_ServerStreamMessages_, context, request, true, tag);
}

::grpc::ClientAsyncReader< ::helloworld::MessageFromServer>* HelloService::Stub::PrepareAsyncServerStreamMessagesRaw(::grpc::ClientContext* context, const ::helloworld::MessageFromClient& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncReaderFactory< ::helloworld::MessageFromServer>::Create(channel_.get(), cq, rpcmethod_ServerStreamMessages_, context, request, false, nullptr);
}

::grpc::ClientReaderWriter< ::helloworld::MessageFromClient, ::helloworld::MessageFromServer>* HelloService::Stub::BidirectionalStreamMessagesRaw(::grpc::ClientContext* context) {
  return ::grpc::internal::ClientReaderWriterFactory< ::helloworld::MessageFromClient, ::helloworld::MessageFromServer>::Create(channel_.get(), rpcmethod_BidirectionalStreamMessages_, context);
}

::grpc::ClientAsyncReaderWriter< ::helloworld::MessageFromClient, ::helloworld::MessageFromServer>* HelloService::Stub::AsyncBidirectionalStreamMessagesRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq, void* tag) {
  return ::grpc::internal::ClientAsyncReaderWriterFactory< ::helloworld::MessageFromClient, ::helloworld::MessageFromServer>::Create(channel_.get(), cq, rpcmethod_BidirectionalStreamMessages_, context, true, tag);
}

::grpc::ClientAsyncReaderWriter< ::helloworld::MessageFromClient, ::helloworld::MessageFromServer>* HelloService::Stub::PrepareAsyncBidirectionalStreamMessagesRaw(::grpc::ClientContext* context, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncReaderWriterFactory< ::helloworld::MessageFromClient, ::helloworld::MessageFromServer>::Create(channel_.get(), cq, rpcmethod_BidirectionalStreamMessages_, context, false, nullptr);
}

HelloService::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      HelloService_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< HelloService::Service, ::helloworld::HelloRequest, ::helloworld::HelloReply>(
          std::mem_fn(&HelloService::Service::SayHello), this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      HelloService_method_names[1],
      ::grpc::internal::RpcMethod::CLIENT_STREAMING,
      new ::grpc::internal::ClientStreamingHandler< HelloService::Service, ::helloworld::MessageFromClient, ::helloworld::MessageFromServer>(
          std::mem_fn(&HelloService::Service::ClientStreamMessages), this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      HelloService_method_names[2],
      ::grpc::internal::RpcMethod::SERVER_STREAMING,
      new ::grpc::internal::ServerStreamingHandler< HelloService::Service, ::helloworld::MessageFromClient, ::helloworld::MessageFromServer>(
          std::mem_fn(&HelloService::Service::ServerStreamMessages), this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      HelloService_method_names[3],
      ::grpc::internal::RpcMethod::BIDI_STREAMING,
      new ::grpc::internal::BidiStreamingHandler< HelloService::Service, ::helloworld::MessageFromClient, ::helloworld::MessageFromServer>(
          std::mem_fn(&HelloService::Service::BidirectionalStreamMessages), this)));
}

HelloService::Service::~Service() {
}

::grpc::Status HelloService::Service::SayHello(::grpc::ServerContext* context, const ::helloworld::HelloRequest* request, ::helloworld::HelloReply* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status HelloService::Service::ClientStreamMessages(::grpc::ServerContext* context, ::grpc::ServerReader< ::helloworld::MessageFromClient>* reader, ::helloworld::MessageFromServer* response) {
  (void) context;
  (void) reader;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status HelloService::Service::ServerStreamMessages(::grpc::ServerContext* context, const ::helloworld::MessageFromClient* request, ::grpc::ServerWriter< ::helloworld::MessageFromServer>* writer) {
  (void) context;
  (void) request;
  (void) writer;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status HelloService::Service::BidirectionalStreamMessages(::grpc::ServerContext* context, ::grpc::ServerReaderWriter< ::helloworld::MessageFromServer, ::helloworld::MessageFromClient>* stream) {
  (void) context;
  (void) stream;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace helloworld
