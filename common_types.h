
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

  description: common types used by others
*/


#ifndef _COMMON_TYPES_H_
#define _COMMON_TYPES_H_

#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/date_time/gregorian/greg_date.hpp>
#include <boost/date_time/gregorian/parsers.hpp>
#include <boost/date_time/gregorian/formatters.hpp>

using std::string;
using boost::property_tree::ptree;
using boost::gregorian::date;
using boost::gregorian::from_string;
using boost::gregorian::to_iso_extended_string;

const unsigned int numCellsInRow = 6;
const string       cashFlowList [] = { "приход", "расход" };


/**
 * @brief The xmlRow struct represents row from table from content.xml file
 */
struct xmlRow
{
  string cashflow; // приход/расход
  string source;   // Лента, eurospar e.t.c
  date dateP;      // date of purchase (ex 2017-02-12)
  string item;     // what is bought
  float price;     // how much does it cost
  float amount;    // how many items are bought
};

/**
 * @brief The oneItem struct represents one item and his total price
 */
struct oneItemP
{
  date dateP;  // date of purchase (ex 2017-02-12)
  string item; // what is bought
  float price; // how much does it cost
};

struct oneItemA
{
  string item;  // what is bought
  float amount; // how many items is bought
};

/**
 * @brief The purchase struct represents common amount of money for
 *        one cashflow-source-date
 */
struct purchase
{
  string cashflow; // inflow/outflow
  string source;   // Лента, eurospar
  date dateP;      // date of purchase (ex 2017-02-12)
  float flow;      // common amount of money for this purchase
};


/**
 * @brief The cashFlow struct represents returned value for statistic
 */
struct cashFlow
{
  float inflow;  // cashflow input for this month (приход)
  float outflow; // cashflow output for this month (расход)
};


enum perioud
{
  monthP,
  yearP
};

#endif
