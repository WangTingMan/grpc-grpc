#include "hellostreamingworld.grpc.pb.h"
#include <grpcpp/grpcpp.h>

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using hellostreamingworld::HelloRequest;
using hellostreamingworld::HelloReply;
using hellostreamingworld::MultiGreeter;

int main()
{
  std::shared_ptr<Channel> channel = grpc::CreateChannel(
    "localhost:50051", grpc::InsecureChannelCredentials() );

  std::unique_ptr<MultiGreeter::Stub> stub_;
  stub_ = MultiGreeter::NewStub( channel );

  HelloRequest request;
  request.set_name( "request message");
  request.set_num_greetings( "1 number" );

  // Container for the data we expect from the server.
  HelloReply reply;

  // Context for the client. It could be used to convey extra information to
  // the server and/or tweak certain RPC behaviors.
  ClientContext context;

  std::unique_ptr< ::grpc::ClientReader< ::hellostreamingworld::HelloReply>> ret;
  ret = stub_->sayHello( &context, request );

  ret->Read( &reply );
  std::string message_ =  reply.message();
  std::cout << "Received the message: " << message_ << std::endl;

  ret->Read( &reply );
  message_ = reply.message();
  std::cout << "Received the message: " << message_ << std::endl;

  return 0;
}
