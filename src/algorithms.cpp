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

#include "algorithms.h"



/**
  INTERNAL ROUTINES
*/
static int safe_create_dir(const std::string &sPath);
static std::map<boost::gregorian::date, cashFlow> yearlyMonthlySimple(const std::vector<xmlRow> &data,
                                               boost::gregorian::date from,
                                               boost::gregorian::date to,
                                               perioud per);



/**
  EXTERNAL ROUTINES
 */
std::vector<purchase> dailyCarts(const std::vector<xmlRow> &data, boost::gregorian::date from, boost::gregorian::date to)
{
  std::map<std::string, purchase*> tmpResult; /* map to fast search items from vector */
  std::vector<purchase>       result;    /* resulted vector */

  // go through data
  for(auto it = data.begin(); it != data.end(); it++)
  {
    // make key string cashflow-source-date
    std::string keyString = to_iso_extended_string(it->dateP) + it->cashflow + it->source;

    // check that item in date range
    if( it->dateP < from || it->dateP > to )
    {
      /*
      std::cerr << __FILE__ << " " << __LINE__ << " " << __FUNCTION__ << std::endl
           << "NOTICE. item doesn't fit to date range. Skip this row."
           << std::endl;
       */
      continue;
    }

    // check if map already has such date item
    std::map<std::string, purchase*>::iterator itFound = tmpResult.find(keyString);

    // if nothing was found insert item
    if( itFound == tmpResult.end() )
    {
      purchase tmpPurchase = { it->cashflow, it->source, it->dateP, 0.0 };

      if( it->cashflow == cashFlowList [0] ||
          it->cashflow == cashFlowList [1] )
      {
        tmpPurchase.flow += it->price * it->amount;
      }
      else
      {
        std::cerr << __FILE__ << " " << __LINE__ << " " << __FUNCTION__ << std::endl
             << "ERROR. Unknown cashflow type. Skip this row."
             << std::endl;
        continue;
      }

      // add to result vector
      result.push_back(tmpPurchase);

      // add to map and check errors
      std::pair<std::map<std::string, purchase*>::iterator, bool> finish =
          tmpResult.insert(std::pair<std::string, purchase*>(keyString, &(result.back())));

      // if insert fail
      if(!finish.second)
      {
        std::cerr << __FILE__ << " " << __LINE__ << " " << __FUNCTION__ << std::endl
             << "ERROR. Handling of " << *it << " failed."
             << std::endl;
      } // END if
    }
    else
    { // if item was found

      if( it->cashflow == cashFlowList [0] ||
          it->cashflow == cashFlowList [1] )
      {
        itFound->second->flow += it->price * it->amount;
      }
      else
      {
        std::cerr << __FILE__ << " " << __LINE__ << " " << __FUNCTION__ << std::endl
             << "ERROR. Unknown cashflow type. Skip this row."
             << std::endl;
        continue;
      }

    } // END if

  } // END of

  // make resulted

  return result;
}


std::map<boost::gregorian::date, cashFlow> monthlySimple(const std::vector<xmlRow> &data, boost::gregorian::date from, boost::gregorian::date to)
{
  return yearlyMonthlySimple(data, from, to, monthP);
}


std::map<boost::gregorian::date, cashFlow> yearlySimple(const std::vector<xmlRow> &data, boost::gregorian::date from, boost::gregorian::date to)
{
  return yearlyMonthlySimple(data, from, to, yearP);
}


std::list<std::list<oneItemP>>
       theMostExpensiveOutflowItemsPerUnit(const std::vector<xmlRow> &data,
                                           long int numberofRanksToReturn,
                                           boost::gregorian::date from,
                                           boost::gregorian::date to)
{
  std::list<std::list<oneItemP>> result;         // result

  // sanity check
  assert(numberofRanksToReturn >= -1);
  if(numberofRanksToReturn == 0)
    return result;

  std::vector<xmlRow> tmpData = data; //
  bool           isFound = false;

  // sort
  // magic trick to sort by descending vector before processing
  sortPrice(tmpData, 2);

  for(auto it = tmpData.begin(); it != tmpData.end(); ++it)
  {
    // check that item in date range
    if( it->dateP < from || it->dateP > to )
    {
      /*
      std::cerr << __FILE__ << " " << __LINE__ << " " << __FUNCTION__ << std::endl
           << "NOTICE. item doesn't fit to date range. Skip this row."
           << std::endl;
       */
      continue;
    }

    // check that item is outflow only
    if( it->cashflow != cashFlowList [1] )
    {
      continue;
    }

    // check if item is already in resul
    // it is important that tmpData has been already sorted
    isFound = false;
    for(auto it2 = result.begin(); it2 != result.end() && !isFound; ++it2)
    {
      for(auto it3 = it2->begin(); it3 != it2->end() && !isFound; ++it3)
      {
        if( it->item == it3->item )
        {
          isFound = true;
        }
      } // END for

      // check if it is item of the same rank
      if( !isFound &&
          it->price == it2->begin()->price )
      {
        oneItemP tmpItem = {it->dateP, it->item, it->price};
        it2->push_back(tmpItem);
        isFound = true;
      }

    } // END for

    // skip already existing item
    if(isFound)
      continue;

    // add new item to the end
    // it is new rank of items
    std::list<oneItemP> tmpResult;
    oneItemP tmpItem = {it->dateP, it->item, it->price};
    tmpResult.push_back(tmpItem);
    result.push_back(tmpResult);

    // check number of found items
    if( numberofRanksToReturn > -1 &&
       (unsigned int)result.size() >= numberofRanksToReturn )
      break;

  } // END for

  return result;
}


std::list<std::list<oneItemA>>
      theMostConsumedItems(const std::vector<xmlRow> &data,
                           long int numberofRanksToReturn,
                           boost::gregorian::date from,
                           boost::gregorian::date to )
{
  std::list<std::list<oneItemA>> result;    //
  std::vector<oneItemA>     resultTmp; // sort list of items

  // sanity check
  assert(numberofRanksToReturn >= -1);
  if(numberofRanksToReturn == 0)
    return result;

  //process data
  for(auto it = data.begin(); it != data.end(); ++it)
  {
    // check that item in date range
    if( it->dateP < from || it->dateP > to )
    {
      /*
      std::cerr << __FILE__ << " " << __LINE__ << " " << __FUNCTION__ << std::endl
           << "NOTICE. item doesn't fit to date range. Skip this row."
           << std::endl;
       */
      continue;
    }

    // check that item is outflow only
    if( it->cashflow != cashFlowList [1] )
    {
      continue;
    }

    bool isFound = false;
    // find item in resultTmp
    for(auto it2 = resultTmp.begin(); it2 != resultTmp.end(); ++it2)
    {

      // if item is found
      if( it->item == it2->item )
      {
        isFound = true;
        // add amount to existing item
        it2->amount += it->amount;
        break;
      } // END if
    } // END for

    // process next item if current already has been found
    if(isFound)
      continue;

    // if it is new item
    oneItemA tmpItem = {it->item, it->amount};
    resultTmp.push_back(tmpItem);

  } // END for

  // sort resultTmp
  sortAmount(resultTmp);

  // create result list
  for(auto it = resultTmp.begin(); it != resultTmp.end(); ++it)
  {
    bool isFound = false;
    // find rank in list
    for(auto it2 = result.begin(); it2 != result.end(); ++it2)
    {
      // skip rank if item from another rank
      if( fabs(it->amount - it2->front().amount) >= 0.01 )
        continue;
      else
      {
        // item is for this rank
        isFound = true;
        // add to this rank
        it2->push_back(*it);
      }
    } // END for

    // add new rank for item
    if( !isFound )
    {
      result.push_back({{it->item, it->amount}});
    }

    // check number of found items
    if( numberofRanksToReturn > -1 &&
       (unsigned int)result.size() >= numberofRanksToReturn )
      break;

  } // END for

  return result;
}


std::ostream &operator <<(std::ostream &os, const xmlRow &row)
{
    os << "cashFlow: " << row.cashflow << std::endl
       << "source: " << row.source << std::endl
       << "dateP: " << to_iso_extended_string(row.dateP) << std::endl
       << "item: " << row.item << std::endl
       << "price: " << row.price << std::endl
       << "amount: " << row.amount;

    return os;
}


void sortDateSource(std::vector<xmlRow> &rows, const int sortOrder)
{
  if( 1 == sortOrder ) // ascending
    sort(rows.begin(), rows.end(),[](xmlRow a, xmlRow b){
          return ( a.dateP != b.dateP ) ? (a.dateP < b.dateP) : (a.source < b.source);
        });
  else if( 2 == sortOrder ) // descending
    sort(rows.begin(), rows.end(),[](xmlRow a, xmlRow b){
          return ( a.dateP != b.dateP ) ? (a.dateP > b.dateP) : (a.source > b.source);
        });
  else
    std::cerr << __FILE__ << " " << __LINE__ << " " << __FUNCTION__ << std::endl
         << "ERROR: unknown order";
}


void sortPrice(std::vector<xmlRow> &rows, const int sortOrder)
{
  if( 1 == sortOrder ) // ascending
    sort(rows.begin(), rows.end(),[](xmlRow a, xmlRow b){
          return (a.price < b.price);
        });
  else if( 2 == sortOrder ) // descending
    sort(rows.begin(), rows.end(),[](xmlRow a, xmlRow b){
          return (a.price > b.price);
        });
  else
    std::cerr << __FILE__ << " " << __LINE__ << " " << __FUNCTION__ << std::endl
         << "ERROR: unknown order";
}

void sortAmount(std::vector<oneItemA> &rows, const int sortOrder)
{
  if( 1 == sortOrder ) // ascending
    sort(rows.begin(), rows.end(),[](oneItemA a, oneItemA b){
          return (a.amount < b.amount);
        });
  else if( 2 == sortOrder ) // descending
    sort(rows.begin(), rows.end(),[](oneItemA a, oneItemA b){
          return (a.amount > b.amount);
        });
  else
    std::cerr << __FILE__ << " " << __LINE__ << " " << __FUNCTION__ << std::endl
         << "ERROR: unknown order";
}


int extract_zip(const char *archive, const char *destination)
{
  const std::string ME_("extract_zip");
  struct zip      *za;
  struct zip_file *zf;
  struct zip_stat sb;
  char            buf[100];
  int             err;
  int             i, len;
  int             fd;
  zip_uint64_t    sum;

  if((za = zip_open(archive, 0, &err)) == NULL)
  {
      zip_error_to_str(buf, sizeof(buf), err, errno);
      std::cerr << ME_ << ": can't open zip archive " << archive
           << ", buf " << buf;
      return 1;
  }
 
  for(i = 0; i < zip_get_num_entries(za, 0); i++)
  {
    if( zip_stat_index(za, i, 0, &sb) )
    {
      std::cerr << ME_ << ": zip_stat_index failed" << std::endl;
    }
    else
    {
      /*
      std::cout << std::endl
           << "Name: " << sb.name << std::endl
           << "Size:" << sb.size << std::endl
           << "mtime: " << (unsigned int)sb.mtime
           << std::endl;
           */

      // create directory if it is necessary
      if( strstr(sb.name, "/") )
      {
        std::string tmpDir(destination);
        tmpDir.append("/").append(sb.name);

        if( safe_create_dir(tmpDir) )
          return 2;
      }
      else
      {
        zf = zip_fopen_index(za, i, 0);
        if(!zf)
        {
          std::cerr << ME_ << ": zip_fopen_index failed, zf = " << zf << std::endl;
          return 3;
        }

        std::string fullPathFileName(destination);
        fullPathFileName.append("/").append(sb.name);

        fd = open(fullPathFileName.c_str(), O_RDWR | O_TRUNC | O_CREAT, 0644);
        if(fd < 0)
        {
          std::cerr << ME_ << ": open file " << fullPathFileName.c_str()
               << " from archive " << archive << " failed, fd = " << fd << std::endl;
          return 4;
        }

        sum = 0;
        while(sum != sb.size)
        {
          len = zip_fread(zf, buf, 100);
          if(len < 0)
          {
            std::cerr << ME_ << ": zip_fread failed, len = " << len << std::endl;
            return 5;
          }
          write(fd, buf, len);
          sum += len;
        }
        close(fd);
        zip_fclose(zf);
      } // END if(sb.name

    } // END if(zip_stat_index

  } // END for(i = 0
 
  if(zip_close(za) == -1)
  {
    std::cerr << ME_ << ": can't close zip archive " << archive << std::endl;
    return 10;
  }

  return 0;
}


unsigned int mb_length(const std::string s)
{
  return (s.length() - count_if(s.begin(), s.end(), [](char c)->bool { return (c & 0xC0) == 0x80; }));
}


/**
 * @brief safe_create_dir is a function create absent directories in sPath
 * @param sPath path without trailed "/"
 * @return 0 for success or other positive value for failure
 */
static int safe_create_dir(const std::string &sPath)
{
  const std::string ME_ = "safe_create_dir";

  size_t          pos = 1;

  while( std::string::npos != (pos = sPath.find("/", pos)) )
  {
    std::string tmpPath(std::string(sPath, 0, pos));
    pos++;

    if(mkdir(tmpPath.c_str(), 0755) < 0)
    {
      if(errno != EEXIST)
      {
        std::cerr << ME_ << ": mkdir failed for " << tmpPath.c_str() << std::endl;
        return 1;
      }
    }

  }

    return 0;
}


/**
 * @brief yearlyMonthlySimple calculate cashflow for every perioud of time (month, year)
 *        from fromDate to toDate in vector data
 * @param data from ods file to process
 * @param fromDate low date bound of processed data
 * @param toDate up date bound of processed data
 * @return map of inflow/outflow for every perioud (month, year)
 */
static std::map<boost::gregorian::date, cashFlow> yearlyMonthlySimple(const std::vector<xmlRow> &data,
                                               boost::gregorian::date from,
                                               boost::gregorian::date to,
                                               perioud per)
{
  std::map<boost::gregorian::date, cashFlow> result;

  // go through data
  for(auto it = data.begin(); it != data.end(); it++)
  {
    boost::gregorian::date::year_type  tmpYear  = it->dateP.year();
    boost::gregorian::date             tmpStartDate;

    if( monthP == per )
    {
      boost::gregorian::date::month_type tmpMonth = it->dateP.month();
      tmpStartDate = boost::gregorian::date(tmpYear, tmpMonth, 1); // first day in processed month
    }
    else if( yearP == per )
    {
      tmpStartDate = boost::gregorian::date(tmpYear, 1, 1); // first day in prcessed year
    }

    // check that item in date range
    if( it->dateP < from || it->dateP > to )
    {
      /*
      std::cerr << __FILE__ << " " << __LINE__ << " " << __FUNCTION__ << std::endl
           << "NOTICE. item doesn't fit to date range. Skip this row."
           << std::endl;
       */
      continue;
    }

    // check if map already has such date item
    std::map<boost::gregorian::date, cashFlow>::iterator itFound = result.find(tmpStartDate);

    // if nothing was found insert item
    if( itFound == result.end() )
    {
      cashFlow tmpCashFlow = {0, 0};

      if(it->cashflow == cashFlowList [0])
      {
        tmpCashFlow.inflow += it->price * it->amount;
      }
      else if(it->cashflow == cashFlowList [1])
      {
        tmpCashFlow.outflow += it->price * it->amount;
      }
      else
      {
        std::cerr << __FILE__ << " " << __LINE__ << " " << __FUNCTION__ << std::endl
             << "ERROR. Unknown cashflow type. Skip this row."
             << std::endl;
        continue;
      }

      // check errors
      std::pair<std::map<boost::gregorian::date, cashFlow>::iterator, bool> finish =
          result.insert(std::pair<boost::gregorian::date, cashFlow>(tmpStartDate, tmpCashFlow));

      // if insert fail
      if(!finish.second)
      {
        std::cerr << __FILE__ << " " << __LINE__ << " " << __FUNCTION__ << std::endl
             << "ERROR. Handling of " << *it << " failed."
             << std::endl;
      } // END if
    }
    else
    {
      // if item was found
      if(it->cashflow == cashFlowList [0])
      {
        itFound->second.inflow += it->price * it->amount;
      }
      else if(it->cashflow == cashFlowList [1])
      {
        itFound->second.outflow += it->price * it->amount;
      }
      else
      {
        std::cerr << __FILE__ << " " << __LINE__ << " " << __FUNCTION__ << std::endl
             << "ERROR. Unknown cashflow type. Skip this row."
             << std::endl;
        continue;
      }
    } // END if

  } // END of

  return result;
}
