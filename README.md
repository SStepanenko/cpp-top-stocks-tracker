# cpp-top-stocks-tracker

Top stocks tracker test task: implement a class that notifies a customer of top gainers/top losers on the stock market.
Full task description: doc/Top_stocks_test_task.pdf

Project is implemented in Visual Studio 2013 for Win32 platform on C++ programming language (features of C++ 11 standard are used).

**Coding style:**  [JSF-AV rules](http://www.stroustrup.com/JSF-AV-rules.pdf)

## Folders Structure

* Project of top stocks tracker C++ static library: top_stocks/top_stocks.

* Project of demo application: top_stocks/top_stocks_demo_app.
  
  Application just randomly updates prices of stocks and outputs top gainers and top losers on console in the following format: [top_stocks_demo_app_output.txt](https://github.com/SStepanenko/cpp-top-stocks-tracker/blob/master/doc/top_stocks_demo_app_output.txt)
 
 **Built version of demo application:** [cpp-top-stocks-tracker-demo-app.rar](https://drive.google.com/open?id=0BwxA95Z8HZsRUU1EVlRaaDZfWWc)
 
 Before executing of application adjust settings of console window so that tables are displayed correctly.
 I use the following parameters of Layout: Screen Buffer Size (Width = 142, Height = 48), Window Size (Width = 142, Height = 48).
 
* Project of library tests: top_stocks/top_stocks_test.

To build and execute unit tests project put the folder 3rd_party_libs with headers and built googletest libraries to the folder of this repository. 
You can take 3rd_party_libs folder from here: https://github.com/SStepanenko/my-cpp-test-tasks/tree/master/3rd_party_libs
Or you can download and build googletest library by yourself.

* Visual Studio Solution which includes all projects described above: top_stocks/top_stocks_lib.sln
