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

#include "content_reader.h"

#define ATTR "<xmlattr>"


ContentReader::ContentReader(const string _odsFileName)
 :ODSReader(_odsFileName), contentFileName("content.xml")
{
    // Parse the XML into the property tree.
    read_xml(contentFileName, tree);
}


string ContentReader::getContentName() const
{
    return contentFileName;
}


vector<string> ContentReader::getTablesList() const
{
    const string path          = "office:document-content.office:body.office:spreadsheet";
    ptree tree2                = tree.get_child(path);
    const string nodeTable     = "table:table";
    const string nodeTableName = "table:name";

    vector<string> tables;

    pair<ptree::const_assoc_iterator, ptree::const_assoc_iterator> result = tree2.equal_range(nodeTable);
    for( ptree::const_assoc_iterator it = result.first; it != result.second; ++it )
    {
//      cout << "find: " << it->first << endl;

      // xmlattr
      pair<ptree::const_assoc_iterator, ptree::const_assoc_iterator> result2 = it->second.get_child(ATTR).equal_range(nodeTableName);
      for( ptree::const_assoc_iterator it2 = result2.first; it2 != result2.second; ++it2 )
      {
//        cout << "  attr: " << it2->first << " => " << it2->second.data() << endl;
        tables.push_back(it2->second.data());
      }
    }

    return tables;
}


vector<xmlRow> ContentReader::getTable() const
{
    vector<xmlRow> table;

    return table;
}


ContentReader::~ContentReader()
{
}
