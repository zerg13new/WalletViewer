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

#include <vector>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <zip.h>
#include <boost/date_time/gregorian/greg_date.hpp>
#include "common_types.h"

using std::vector;
using boost::gregorian::date;

/**
  return sorted montly inflow/outflow
*/
vector<cashFlow> montlySimple(vector<xmlRow>, date fromDate = date(1970, 01, 01),
                                     date toDate = date(2100, 01, 01));

/**
  return sorted yearly inflow/outflow
*/
vector<cashFlow> yearlySimple(vector<xmlRow>, date fromDate = date(1970, 01, 01),
                                     date to = date(1970, 01, 01));

/**
  return number of most expensive items from source
*/
vector<cashFlow> mostExpensiveItems(vector<xmlRow>, unsigned int numberofItemsToReturn = 1);

/**
  extract files from *.zip archive to destination folder
*/
int extract_zip(const char *zipArchiveName, const char *destination);

#endif
