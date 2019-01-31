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
#include <map>
#include <list>
#include <cmath>
#include "common_types.h"


/**
 * @brief dailyCarts calculate each cart (all purchases) for each day in
 *        each market
 * @param data from ods file to process
 * @param fromDate low date bound of processed data
 * @param toDate up date bound of processed data
 * @return vector of purchase
 */
std::vector<purchase> dailyCarts(const std::vector<xmlRow> &data,
                                  boost::gregorian::date fromDate = boost::gregorian::date(1970, 01, 01),
                                  boost::gregorian::date toDate = boost::gregorian::date(2100, 01, 01));

/**
 * @brief monthlySimple calculate cashflow for every month for perioud of time
 *        from fromDate to toDate in vector data
 * @param data from ods file to process
 * @param fromDate low date bound of processed data
 * @param toDate up date bound of processed data
 * @return map of date=>cashFlow pair for every month for requested perioud
 *         note: date is a first date of each found month.
 *         E.g. 2017.01.01 for 2017.01.05
 */
std::map<boost::gregorian::date, cashFlow> monthlySimple(const std::vector<xmlRow> &data,
                              boost::gregorian::date fromDate = boost::gregorian::date(1970, 01, 01),
                              boost::gregorian::date toDate = boost::gregorian::date(2100, 01, 01));

/**
 * @brief yearlySimple calculate cashflow for every year for perioud of time
 *        from fromDate to toDate in vector data
 * @param data from ods file to process
 * @param fromDate low date bound of processed data
 * @param toDate up date bound of processed data
 * @return map of date=>cashFlow elements for every year for requested perioud
 */
std::map<boost::gregorian::date, cashFlow> yearlySimple(const std::vector<xmlRow> &data,
                              boost::gregorian::date fromDate = boost::gregorian::date(1970, 01, 01),
                              boost::gregorian::date toDate = boost::gregorian::date(2100, 01, 01));

/**
 * @brief theMostExpensiveOutflowItemsPerUnit return most expensive outflow items from data
 * @param data data from ods file to process
 * @param numberofItemsToReturn number of item to return
 *        Notes: -1 is for all found items (default behaviour)
 * @param fromDate low date bound of processed data
 * @param toDate up date bound of processed data
 * @return list of list of items
 * Notes: If several items have equal price then several will be returned in
 *        the same rank category.
 *        Rank - items with equal price
 *         returned value is associated with ranked list of items, like
 *                [0] - the most expensive items ({2017.01.02, burger, 20$}, {2017.03.22, melon, 20$})
 *                [numberofItemsToReturn - 1] - the last the most expensive items ({bread, 5$})
 *                Each rank position is a order of items with the same price
 */
std::list<std::list<oneItemP>>
      theMostExpensiveOutflowItemsPerUnit(const std::vector<xmlRow> &data,
                                          long int numberofRanksToReturn = -1,
                                          boost::gregorian::date fromDate = boost::gregorian::date(1970, 01, 01),
                                          boost::gregorian::date toDate = boost::gregorian::date(2100, 01, 01));

/**
 * @brief theMostConsumedItems returns most consumed items from data
 * @param data data from ods file to process
 * @param numberofItemsToReturn number of item to return
 *        Notes: -1 is for all found items (default behaviour)
 * @param fromDate low date bound of processed data
 * @param toDate up date bound of processed data
 * @return list of list of items (sorted by descending) with amount of each item
 * Notes: returned result holds the hall order of items instead of certain
 *        number of items because the hall scope of data will be processed anyway.
 *        Caller should decide how many items necessary after function execution.
 */
std::list<std::list<oneItemA>>
      theMostConsumedItems(const std::vector<xmlRow> &data,
                           long int numberofRanksToReturn = -1,
                           boost::gregorian::date fromDate = boost::gregorian::date(1970, 01, 01),
                           boost::gregorian::date toDate = boost::gregorian::date(2100, 01, 01));


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
std::ostream &operator <<(std::ostream &os, const xmlRow &row);

/**
 * @brief sortDateSource to sort vector of xml rows in order by date + source
 * @param rows vector of xmlRow rows to sort
 * @param sortOrder 1 - ascending (default), 2 - descending
 */
void sortDateSource(std::vector<xmlRow> &rows, const int sortOrder = 1);

/**
 * @brief sortPrice to sort vector of xml rows in order by price
 * @param rows vector of xmlRow rows to sort
 * @param sortOrder 1 - ascending (default), 2 - descending
 */
void sortPrice(std::vector<xmlRow> &rows, const int sortOrder = 1);

/**
 * @brief sortAmount to sort vector of oneItemA in order by amount
 * @param rows vector of oneItemA to sort
 * @param sortOrder 1 - ascending , 2 - descending (default)
 */
void sortAmount(std::vector<oneItemA> &rows, const int sortOrder = 2);

/**
 * @brief mb_length Find length of multibyte utf8 string
 * @param s multibyte string in utf8
 * @return length utf8 string
 */
unsigned int mb_length(const std::string s);

#endif
