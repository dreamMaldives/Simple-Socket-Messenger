#include "MessengerClient.h"
#include "SocketException.h"
#include <iostream>
#include <string>

int main ( int argc, char* argv[] )
{
  try
    {

      MessengerClient client( 30000 );

    }
  catch ( SocketException& e )
    {
      std::cout << "Exception was caught:" << e.description() << "\n";
    }

  return 0;
}
