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

#ifndef _CONTENT_READER_H_
#define _CONTENT_READER_H_

#include <string>
#include <vector>
#include <set>
#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/date_time/gregorian/greg_date.hpp>

#include "common_types.h"
#include "ods_reader.h"

using std::string;
using std::vector;
using std::pair;
using boost::property_tree::ptree;


/**
 * @brief The ContentReader class For reading content.xml file from *.ods file
 */
class ContentReader: public ODSReader
{
  public:
  /**
     * @brief ContentReader main constructor
     * @param _odsFileName full path to ods.file
     *         e.g. /tmp/test.ods
     */
    ContentReader(const string _odsFileName);
    virtual ~ContentReader();

    /**
      get content file name
    */
    string getContentName() const;

    /**
      get list of tables from content.xml file
    */
    vector<string> getTablesList() const;

    /**
     get table in vector view to process futher
    */
    vector<xmlRow> getTable() const;

  private:
    explicit ContentReader();
    explicit ContentReader(const ContentReader &obj);

  protected:
    const string contentFileName;
    ptree tree;
};

#endif
