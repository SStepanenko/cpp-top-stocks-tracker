////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @file top_stocks_demo_app.cpp
/// @brief Main file of the top stocks demo application project, contains application entry point.
/// @author Sergey Stepanenko (sergey.stepanenko.27@gmail.com)
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "pch.h"

using namespace std;

int main(int argc, char* argv[])
{
  int execution_result = EXIT_SUCCESS;

  try
  {
    Top_stocks_app top_stocks_app;

    top_stocks_app.run(); // exception
  }
  // Handle exceptions.
  catch (exception& error)
  {
    printf("ERROR: %s\n", error.what());
   
    execution_result = EXIT_FAILURE;
  }

  return execution_result;
}
