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

  description: algorithms for statistic calculation
*/


#ifndef _ALGORITHMS_H_H
#define _ALGORITHMS_H_H

#include <iostream>
#include <vector>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <zip.h>
#include <boost/date_time/gregorian/greg_date.hpp>
#include <algorithm>
#include "common_types.h"

using std::vector;
using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::ostream;
using std::sort;
using std::string;
using boost::gregorian::date;


const string cashFlowList [] = { "приход", "расход" };


/**
 * @brief montlySimple calculate cashflow for every month for perioud of time
 *        from fromDate to toDate in vector data
 * @param data from ods file to process
 * @param fromDate low date bound of processed data
 * @param toDate up date bound of processed data
 * @return sorted vector of cashFlow elements for every month for requested perioud
 */
vector<cashFlow> montlySimple(const vector<xmlRow> &data,
                              date fromDate = date(1970, 01, 01),
                              date toDate = date(2100, 01, 01));


/**
 * @brief yearlySimple calculate cashflow for every year for perioud of time
 *        from fromDate to toDate in vector data
 * @param data from ods file to process
 * @param fromDate low date bound of processed data
 * @param toDate up date bound of processed data
 * @return sorted vector of cashFlow elements for every year for requested perioud
 */
vector<cashFlow> yearlySimple(const vector<xmlRow> &data,
                              date fromDate = date(1970, 01, 01),
                              date toDate = date(1970, 01, 01));


/**
 * @brief mostExpensiveItems return number of most expensive items from data
 * @param data data from ods file to process
 * @param numberofItemsToReturn number of item to return
 * @return sorted vector of numberofItemsToReturn most expensive elements
 */
vector<cashFlow> mostExpensiveItems(const vector<xmlRow> &data,
                                    unsigned int numberofItemsToReturn = 1);


/**
 * @brief extract_zip Extract files from *.zip archive to destination folder
 * @param archive fill absolete path to arhcieve with archieve name
 *        E.x. \tmp\test.ods
 * @param destination full path to destination folder where files will be
 *        extracted
 * @return 0 for success or other positive value for failure
 */
int extract_zip(const char *zipArchiveName, const char *destination);


/**
 * @brief operator << Function to output xmlRow struct
 * @param os output stream
 * @param row xmlRow struct
 * @return ref to output stream
 */
ostream &operator <<(ostream &os, const xmlRow &row);

/**
 * @brief sortDateSource Function to sort vector of xml rows in order
 *        by date + source
 * @param rows vector of xmlRow rows to sort
 * @param sortOrder 1 - ascending (default), 2 - descending
 */
void sortDateSource(vector<xmlRow> &rows, const int sortOrder = 1);

#endif
