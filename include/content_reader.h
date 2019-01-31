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
#include <boost/lexical_cast/bad_lexical_cast.hpp>

#include "common_types.h"
#include "ods_reader.h"


/**
 * @brief The ContentReader class For reading content.xml file from *.ods file
 */
class ContentReader: public ODSReader
{
  friend std::ostream& operator <<(std::ostream &os, const xmlRow &row);
  public:
  /**
     * @brief ContentReader main constructor
     * @param _odsFileName full path to ods.file
     *         e.g. /tmp/test.ods
     */
    ContentReader(const std::string _odsFileName);

    virtual ~ContentReader();

    /**
     * @brief getContentName Get content file name
     * @return content.xml string
     */
    std::string getContentName() const;

    /**
     * @brief getTablesList Get list of tables from content.xml file.
     *        E.g. Dave, Adriana
     * @return vector of table names string
     */
    std::vector<std::string> getTablesList() const;

    /**
     * @brief getTableData getTable Get data from tableName to further processing
     * @param tableName name of table to be read
     * @return vector of xmlRow
     */
    std::vector<xmlRow> getTableData(const std::string tableName) const;

  private:
    /**
     * @brief ContentReader default constructor isn't used somehow
     */
    explicit ContentReader();

    /**
     * @brief ContentReader copy constructor isn't used somehow
     * @param obj
     */
    explicit ContentReader(const ContentReader &obj);

  protected:
    /**
     * @brief contentFileName content.xml
     */
    const std::string contentFileName;

    /**
     * @brief tree special object contain the hole content.xml tree
     */
    boost::property_tree::ptree tree;
};

#endif
