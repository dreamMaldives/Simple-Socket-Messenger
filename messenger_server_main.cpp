#include "MessengerServer.h"
#include "SocketException.h"
#include <iostream>
#include <string>

int main ( int argc, char* argv[] )
{
  try
    {

      MessengerServer server( 30000 );

    }
  catch ( SocketException& e )
    {
      std::cout << "Exception was caught:" << e.description() << "\n";
    }

  return 0;
}
