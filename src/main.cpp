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
#include <clocale>

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
  map<date, cashFlow> stat;
  unsigned int answer;
  const unsigned int wideF = 12;

  cout << endl;
  cout << "Start main" << endl;

//  ODSReader("/home/xxx/Work/payment_cli/test.ods");

//  ContentReader test("/home/xxx/Work/payment_cli/test.ods");
//  ContentReader test("/home/xxx/Work/payment_cli/test_2.ods");
    ContentReader test("/home/xxx/Work/payment.ods");


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

  // montly statistic in simple formatted table
  if(0)
  {
    // get statistic for month
    stat = monthlySimple(data);

    // header
    cout << setw(wideF) << "date"
         << setw(wideF) << "inflow(+)"
         << setw(wideF) << "outflow(-)"
         << endl;

    for(auto &it: stat)
    {
      // show in formated table
      cout << setw(wideF) << to_iso_extended_string(it.first)
           << std::showpoint << std::fixed << std::setprecision(2)
           << setw(wideF) << it.second.inflow
           << setw(wideF) << it.second.outflow << endl;
    }
  }

  // monthly statistic in scv formatted table
  if(0)
  {
    // get statistic for month
    stat = monthlySimple(data);

    // header
    cout << setw(wideF) << "date"
         << setw(wideF) << "inflow(+)"
         << setw(wideF) << "outflow(-)"
         << endl;

    for(auto &it: stat)
    {
      cout << to_iso_extended_string(it.first) << " ; "
           << std::showpoint << std::fixed << std::setprecision(2)
           << it.second.inflow << ";"
           << setw(wideF) << it.second.outflow << endl;
    }
  }

  // yearly statistic in simple formatted table
  if(0)
  {
    // get statistic for month
    stat = yearlySimple(data);

    // header
    cout << setw(wideF) << "date"
         << setw(wideF) << "inflow(+)"
         << setw(wideF) << "outflow(-)"
         << endl;

    for(auto &it: stat)
    {
      // show in formated table
      cout << setw(wideF) << to_iso_extended_string(it.first)
           << std::showpoint << std::fixed << std::setprecision(2)
           << setw(wideF) << it.second.inflow
           << setw(wideF) << it.second.outflow << endl;
    }
  }


  // daily carts in simple formated table
  if(0)
  {
    vector<purchase> stat2 = dailyCarts(data);

    // header
    cout << setw(wideF) << "cash flow"
         << setw(wideF) << "date"
         << setw(wideF) << "source"
         << setw(wideF) << "flow"
         << endl;

    for(auto &it: stat2)
    {

      cout << setw(wideF) << it.cashflow
           << setw(wideF) << to_iso_extended_string(it.dateP)
           << setw(wideF) << it.source
           << std::showpoint << std::fixed << std::setprecision(2)
           << setw(wideF) << it.flow << endl;
    }
  }

  // show the most expensive items
  if(0)
  {

    list<list<oneItemP>> stat2 = theMostExpensiveOutflowItemsPerUnit(data, 20);
    unsigned int i = 0;

    // header
    cout << "rank"
         << setw(wideF - 4) << "date"
         << setw(wideF * 2) << "item"
         << setw(wideF) << "totalPrice"
         << endl;

    for(auto &it: stat2)
    {
      cout << "rank: " << (i + 1) << endl;
      for(auto &it2: it)
      {
        unsigned int wideItem = (wideF * 2 > mb_length(it2.item)) ?
                                (wideF * 2 - mb_length(it2.item)) :
                                (0);
        cout << setw(wideF)
             << setw(wideF) << to_iso_extended_string(it2.dateP)
             << string(wideItem, ' ')
             << it2.item
//             << "(" << mb_length(it2.item) << ")"
             << std::showpoint << std::fixed << std::setprecision(2)
             << setw(wideF) << it2.price << endl;

      } // END for

      i++;
    } // END for
  }

  // show the most consumed items
  if(1)
  {

    list<list<oneItemA>> stat2 = theMostConsumedItems(data, 10);
    unsigned int i = 0;

    // header
    cout << "rank"
         << setw(wideF * 2) << "item"
         << setw(wideF) << "amount"
         << endl;

    for(auto &it: stat2)
    {
      cout << "rank: " << (i + 1) << endl;
      for(auto &it2: it)
      {
        unsigned int wideItem = (wideF * 2 > mb_length(it2.item)) ?
                                (wideF * 2 - mb_length(it2.item)) :
                                (0);
        cout
             << string(wideItem, ' ')
             << it2.item
    //             << "(" << mb_length(it2.item) << ")"
             << std::showpoint << std::fixed << std::setprecision(2)
             << setw(wideF) << it2.amount << endl;
       }// END for

      i++;
    } // END for
  }

  return 0;
}

