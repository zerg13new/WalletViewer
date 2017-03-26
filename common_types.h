
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

  description: algorithms for processing table content.xml file
*/


#ifndef _COMMON_TYPES_H_
#define _COMMON_TYPES_H_

#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/date_time/gregorian/greg_date.hpp>

using std::string;
using boost::property_tree::ptree;
using boost::gregorian::date;


/**
 xml row fromtable from content.xml file
*/
struct xmlRow
{
  string cashflow; // inflow/outflow
  string source;   // Лента, eurospar e.t.c
  date dateP;      // date of purchase (ex 2017-02-12)
  string item;     // what is bought
  float price;     // how much does it cost
  float amount;    // how many items is bought
};


/**
 returned value format for statistic
*/
struct cashFlow
{
  date dateC;    // first day of month for current perioud (ex 2017-02-01
                 // for 02-th month)
  float inflow;  // cashflow input for this month
  float outflow; // cashflow output for this month
};

#endif
