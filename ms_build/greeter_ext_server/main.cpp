#include "greeter_ext_service.h"

int main()
{
  GreeterExtService service;
  service.StartOn( "0.0.0.0:8860" );
  int i = 0;
  while( true )
  {
    std::this_thread::sleep_for( std::chrono::seconds( 1 ) );
    if( service.IsBidirectionConnected() )
    {
      service.SendBiDirectionStreamingServiceMessage("Hello this is service side");
    }
  }
  return 0;
}

