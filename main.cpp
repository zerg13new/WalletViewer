/**
  This file is part of CashFlow software. CashFlow it is a software
  for getting statistic of cashflow in your pocket.
  Copyright (C) 2017  Anufriev Sergey

  CashFlow is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  CashFlow is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with CashFlow.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <iostream>
#include <vector>
#include <string>
#include <exception>

#include "ods_reader.h"
#include "content_reader.h"
#include "algorithms.h"

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::exception;
using std::string;
using std::vector;
using std::setw;



//int main(int argc, char **argv)
int main()
{

  vector<string> tables;
  vector<xmlRow> data;
  unsigned int answer;

  cout << "Start main" << endl;

//  ODSReader("/home/xxx/Work/payment_cli/test.ods");

//  ContentReader test("/home/xxx/Work/payment_cli/test.ods");
  ContentReader test("/home/xxx/Work/payment_cli/test_2.ods");

  // find tables in file
  tables = test.getTablesList();

  if(tables.size() == 0)
  {
    cout << "There no tables in file" << endl;
    return 0;
  }
  else
  {
    vector<string>::iterator it;
    unsigned int i = 0;

    cout << "Choose num of table to process: " << endl
         << setw(5) << " Num   " << "Table name" << endl;
    for(it = tables.begin(); it != tables.end(); it++)
    {
      cout << "[" << setw(3) << i++ << "]  " << *it << endl;
    }
    // reinitialize i, use like a size of tables
    i--;

    // read user answer
    do
    {
      cin >> answer;
    }while( answer > i );

    cout << "Read " << tables[answer] << " table" << endl;

  } // END if(tables.size()

  // get data from table
  data = test.getTableData(tables[answer]);

  // sort data
  sortDateSource(data);

  for( auto &it: data )
  {
    cout << it << endl << endl;
  }

  return 0;
}

