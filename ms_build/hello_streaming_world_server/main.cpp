#include <iostream>
#include <memory>
#include <string>

#include <grpcpp/grpcpp.h>
#include "hellostreamingworld.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::ServerBuilder;
using grpc::Server;
using grpc::Status;
using hellostreamingworld::HelloRequest;
using hellostreamingworld::HelloReply;
using hellostreamingworld::MultiGreeter;

class GreeterServiceImpl final : public MultiGreeter::Service
{
  virtual ::grpc::Status sayHello
    (
    ::grpc::ServerContext* context,
    const ::hellostreamingworld::HelloRequest* request,
    ::grpc::ServerWriter< ::hellostreamingworld::HelloReply>* writer
    )
  {
    std::multimap<grpc::string_ref, grpc::string_ref>const& client_meta = context->client_metadata();
    std::string meta_string("client meta data. ");
    for( auto& ele : client_meta )
    {
      std::string key( ele.first.data(), ele.first.length() );
      std::string value( ele.second.data(), ele.second.length() );
      meta_string.append( "key: " ).append( key ).append( ", value: " ).append( value );
    }
    meta_string.append( "\n" );

    std::string const& name_ = request->name();
    std::string const& name_greetings_ = request->num_greetings();
    meta_string.append( "parameter name: " ).append( name_ );
    meta_string.append( ", parameter name_greeting: " ).append( name_greetings_ ).append( "\n" );
    std::cout << meta_string;

    ::hellostreamingworld::HelloReply reply;
    reply.set_message( "This is my message" );
    writer->Write( reply );

    reply.set_message( "This is another my message" );
    writer->Write( reply );

    reply.set_message( "This is my last message" );
    writer->WriteLast( reply, grpc::WriteOptions());

    return grpc::Status();
  }

};

int main()
{
  std::string server_address( "0.0.0.0:50051" );

  GreeterServiceImpl service;
  ServerBuilder builder;
  // Listen on the given address without any authentication mechanism.
  builder.AddListeningPort( server_address, grpc::InsecureServerCredentials() );
  // Register "service" as the instance through which we'll communicate with
  // clients. In this case it corresponds to an *synchronous* service.
  builder.RegisterService( &service );
  // Finally assemble the server.
  std::unique_ptr<Server> server( builder.BuildAndStart() );
  std::cout << "Server listening on " << server_address << std::endl;

  // Wait for the server to shutdown. Note that some other thread must be
  // responsible for shutting down the server for this call to ever return.
  server->Wait();

  return 0;
}

