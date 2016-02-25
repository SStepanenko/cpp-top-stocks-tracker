# cpp-top-stocks-tracker

Top stocks tracker test task: implement a class that notifies a customer of top gainers/top losers on the stock market.
Full task description: doc/Top_stocks_test_task.pdf

Project is implemented in Visual Studio 2013 for Win32 platform on C++ programming language (features of C++ 11 standard are used).

**Coding style:**  [JSF-AV rules](http://www.stroustrup.com/JSF-AV-rules.pdf)

## Folders Structure

* Project of top stocks tracker C++ static library: top_stocks/top_stocks.

* Project of demo application: top_stocks/top_stocks_demo_app.
  
  Application just randomly updates prices of stocks and outputs top gainers and top losers on console in the following format:

 Top Gainers                                                   Top Losers
 ------------------------------------------------------------  ------------------------------------------------------------
 | Stock ID | First Price ($) | Last Price ($) | Change (%) |  | Stock ID | First Price ($) | Last Price ($) | Change (%) | 
 ------------------------------------------------------------  ------------------------------------------------------------
 | 7849     | 846.00          | 1656.05        | +95.75     |  | 1856     | 522.00          | 89.11          | -82.93     | 
 ------------------------------------------------------------  ------------------------------------------------------------
 | 4774     | 900.00          | 1713.96        | +90.44     |  | 1301     | 334.00          | 85.27          | -74.47     | 
 ------------------------------------------------------------  ------------------------------------------------------------
 | 2635     | 504.00          | 945.35         | +87.57     |  | 2469     | 937.00          | 395.79         | -57.76     | 
 ------------------------------------------------------------  ------------------------------------------------------------
 | 575      | 512.00          | 959.49         | +87.40     |  | 6259     | 316.00          | 142.45         | -54.92     | 
 ------------------------------------------------------------  ------------------------------------------------------------
 | 6574     | 255.00          | 465.94         | +82.72     |  | 5133     | 965.00          | 527.18         | -45.37     | 
 ------------------------------------------------------------  ------------------------------------------------------------
 | 4375     | 812.00          | 1423.11        | +75.26     |  | 3693     | 192.00          | 105.66         | -44.97     | 
 ------------------------------------------------------------  ------------------------------------------------------------
 | 5945     | 340.00          | 589.49         | +73.38     |  | 4411     | 159.00          | 88.85          | -44.12     | 
 ------------------------------------------------------------  ------------------------------------------------------------
 | 2322     | 738.00          | 1277.85        | +73.15     |  | 1157     | 802.00          | 581.37         | -27.51     | 
 ------------------------------------------------------------  ------------------------------------------------------------
 | 268      | 855.00          | 1458.54        | +70.59     |  | 29       | 56.00           | 55.74          | -0.46      | 
 ------------------------------------------------------------  ------------------------------------------------------------
 | 2381     | 840.00          | 1425.98        | +69.76     |  |          |                 |                |            | 
 ------------------------------------------------------------  ------------------------------------------------------------
 
 **Built version of demo application:** [cpp-top-stocks-tracker-demo-app.rar](https://drive.google.com/open?id=0BwxA95Z8HZsRUU1EVlRaaDZfWWc)
 
 Before executing of application adjust settings of console window so that tables are displayed correctly.
 I use the following parameters of Layout: Screen Buffer Size (Width = 142, Height = 48), Window Size (Width = 142, Height = 48).
 
* Project of library tests: top_stocks/top_stocks_test.

To build and execute unit tests project put the folder 3rd_party_libs with headers and built googletest libraries to the folder of this reposotory. 
You can take 3rd_party_libs folder from here: https://github.com/SStepanenko/my-cpp-test-tasks/tree/master/3rd_party_libs
Or you can download and build googletest library by yourself.

* Visual Studio Solution wich includes all projects described above: top_stocks/top_stocks_lib.sln
