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


//int main(int argc, char **argv)
int main()
{

  std::vector<std::string> tables;
  std::vector<xmlRow> data;
  std::map<boost::gregorian::date, cashFlow> stat;
  unsigned int answer;
  const unsigned int wideF = 12;

  std::cout << std::endl;
  std::cout << "Start main" << std::endl;

//  ODSReader("/home/xxx/Work/payment_cli/test.ods");

//  ContentReader test("/home/xxx/Work/payment_cli/test.ods");
//  ContentReader test("/home/xxx/Work/payment_cli/test_2.ods");
    ContentReader test("/home/xxx/Work/payment.ods");


  // find tables in file
  tables = test.getTablesList();

  if(tables.size() == 0)
  {
    std::cout << "There no tables in file" << std::endl;
    return 0;
  }
  else
  {
    std::vector<std::string>::iterator it;
    unsigned int i = 0;

    std::cout << "Choose num of table to process: " << std::endl
         << std::setw(5) << " Num   " << "Table name" << std::endl;
    for(it = tables.begin(); it != tables.end(); it++)
    {
      std::cout << "[" << std::setw(3) << i++ << "]  " << *it << std::endl;
    }
    // reinitialize i, use like a size of tables
    i--;

    // read user answer
    do
    {
      std::cin >> answer;
    }while( answer > i );

    std::cout << "Read " << tables[answer] << " table" << std::endl;

  } // END if(tables.size()

  // get data from table
  data = test.getTableData(tables[answer]);

  // montly statistic in simple formatted table
  if(0)
  {
    // get statistic for month
    stat = monthlySimple(data);

    // header
    std::cout << std::setw(wideF) << "date"
         << std::setw(wideF) << "inflow(+)"
         << std::setw(wideF) << "outflow(-)"
         << std::endl;

    for(auto &it: stat)
    {
      // show in formated table
      std::cout << std::setw(wideF) << boost::gregorian::to_iso_extended_string(it.first)
           << std::showpoint << std::fixed << std::setprecision(2)
           << std::setw(wideF) << it.second.inflow
           << std::setw(wideF) << it.second.outflow << std::endl;
    }
  }

  // monthly statistic in scv formatted table
  if(0)
  {
    // get statistic for month
    stat = monthlySimple(data);

    // header
    std::cout << std::setw(wideF) << "date"
         << std::setw(wideF) << "inflow(+)"
         << std::setw(wideF) << "outflow(-)"
         << std::endl;

    for(auto &it: stat)
    {
      std::cout << boost::gregorian::to_iso_extended_string(it.first) << " ; "
           << std::showpoint << std::fixed << std::setprecision(2)
           << it.second.inflow << ";"
           << std::setw(wideF) << it.second.outflow << std::endl;
    }
  }

  // yearly statistic in simple formatted table
  if(0)
  {
    // get statistic for month
    stat = yearlySimple(data);

    // header
    std::cout << std::setw(wideF) << "date"
         << std::setw(wideF) << "inflow(+)"
         << std::setw(wideF) << "outflow(-)"
         << std::endl;

    for(auto &it: stat)
    {
      // show in formated table
      std::cout << std::setw(wideF) << boost::gregorian::to_iso_extended_string(it.first)
           << std::showpoint << std::fixed << std::setprecision(2)
           << std::setw(wideF) << it.second.inflow
           << std::setw(wideF) << it.second.outflow << std::endl;
    }
  }


  // daily carts in simple formated table
  if(0)
  {
    std::vector<purchase> stat2 = dailyCarts(data);

    // header
    std::cout << std::setw(wideF) << "cash flow"
         << std::setw(wideF) << "date"
         << std::setw(wideF) << "source"
         << std::setw(wideF) << "flow"
         << std::endl;

    for(auto &it: stat2)
    {

      std::cout << std::setw(wideF) << it.cashflow
           << std::setw(wideF) << boost::gregorian::to_iso_extended_string(it.dateP)
           << std::setw(wideF) << it.source
           << std::showpoint << std::fixed << std::setprecision(2)
           << std::setw(wideF) << it.flow << std::endl;
    }
  }

  // show the most expensive items
  if(0)
  {

    std::list<std::list<oneItemP>> stat2 = theMostExpensiveOutflowItemsPerUnit(data, 20);
    unsigned int i = 0;

    // header
    std::cout << "rank"
         << std::setw(wideF - 4) << "date"
         << std::setw(wideF * 2) << "item"
         << std::setw(wideF) << "totalPrice"
         << std::endl;

    for(auto &it: stat2)
    {
      std::cout << "rank: " << (i + 1) << std::endl;
      for(auto &it2: it)
      {
        unsigned int wideItem = (wideF * 2 > mb_length(it2.item)) ?
                                (wideF * 2 - mb_length(it2.item)) :
                                (0);
        std::cout << std::setw(wideF)
             << std::setw(wideF) << boost::gregorian::to_iso_extended_string(it2.dateP)
             << std::string(wideItem, ' ')
             << it2.item
//             << "(" << mb_length(it2.item) << ")"
             << std::showpoint << std::fixed << std::setprecision(2)
             << std::setw(wideF) << it2.price << std::endl;

      } // END for

      i++;
    } // END for
  }

  // show the most consumed items
  if(1)
  {

    std::list<std::list<oneItemA>> stat2 = theMostConsumedItems(data, 10);
    unsigned int i = 0;

    // header
    std::cout << "rank"
         << std::setw(wideF * 2) << "item"
         << std::setw(wideF) << "amount"
         << std::endl;

    for(auto &it: stat2)
    {
      std::cout << "rank: " << (i + 1) << std::endl;
      for(auto &it2: it)
      {
        unsigned int wideItem = (wideF * 2 > mb_length(it2.item)) ?
                                (wideF * 2 - mb_length(it2.item)) :
                                (0);
        std::cout
             << std::string(wideItem, ' ')
             << it2.item
    //             << "(" << mb_length(it2.item) << ")"
             << std::showpoint << std::fixed << std::setprecision(2)
             << std::setw(wideF) << it2.amount << std::endl;
       }// END for

      i++;
    } // END for
  }

  return 0;
}

