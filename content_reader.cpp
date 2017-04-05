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

// path to table node in contenxt.xml file
static const string spreadsheetPath = "office:document-content.office:body.office:spreadsheet";
// xml tag for attributes in context.xml file
static const string xmlattr         = "<xmlattr>";
// node name for spreadsheet in content.xml file
static const string nodeTable       = "table:table";
// xml attribute containing spreadsheet table name
static const string nodeTableName   = "table:name";
// xml attribute containing row nodes
static const string nodeTableRow   = "table:table-row";
// xml attribute containing cell nodes
static const string nodeTableCell   = "table:table-cell";
// xml attribute for cell containing value
static const string nodeOfficeValue   = "office:value-type";
// xml attribute containing text of row node
static const string nodeTableText   = "text:p";


ContentReader::ContentReader(const string _odsFileName)
 :ODSReader(_odsFileName), contentFileName("content.xml")
{
  string tmpFile(this->pathToExtractedODS);

  tmpFile.append("/").append(contentFileName);

  // Parse the XML into the property tree.
  read_xml(tmpFile, tree);
}


string ContentReader::getContentName() const
{
    return contentFileName;
}


vector<string> ContentReader::getTablesList() const
{
  ptree          tree2 = tree.get_child(spreadsheetPath);
  vector<string> tables;

  // find nodes with table:table content
  pair<ptree::const_assoc_iterator, ptree::const_assoc_iterator> result =
      tree2.equal_range(nodeTable);
  for( ptree::const_assoc_iterator it = result.first; it != result.second; ++it )
  {
//      cout << "found: " << it->first << endl;

    // get xmlattr called table:name in node
    pair<ptree::const_assoc_iterator, ptree::const_assoc_iterator> result2 =
        it->second.get_child(xmlattr).equal_range(nodeTableName);
    for( ptree::const_assoc_iterator it2 = result2.first; it2 != result2.second; ++it2 )
    {
//        cout << "  attr: " << it2->first << " => " << it2->second.data() << endl;
      // save found table names in vector
      tables.push_back(it2->second.data());
    }
  }

  return tables;
}


vector<xmlRow> ContentReader::getTableData(const string tableName) const
{
  ptree          tree2 = tree.get_child(string(spreadsheetPath));
  vector<xmlRow> table;
  bool           flag = false; // is table was found

  // Find nodes with table:table content
  // It should be the only table
  pair<ptree::const_assoc_iterator, ptree::const_assoc_iterator> result =
      tree2.equal_range(nodeTable);
  for( ptree::const_assoc_iterator it = result.first; it != result.second && !flag; ++it )
  {
    cout << "found: " << it->first << endl;

    // get xmlattr called table:name in node

    pair<ptree::const_assoc_iterator, ptree::const_assoc_iterator> result2 =
        it->second.get_child(xmlattr).equal_range(nodeTableName);
    for( ptree::const_assoc_iterator it2 = result2.first; it2 != result2.second; ++it2 )
    {
//        cout << "  attr: " << it2->first << " => " << it2->second.data() << endl;
        if( it2->second.data() == tableName )
        {
          flag = true;
          break;
        }
    } // END for

    // if tabeName wasn't found skip node processing
    if( !flag )
      continue;

    // filter only rows
    // reuse result2
    result2 = it->second.equal_range(nodeTableRow);
    for( ptree::const_assoc_iterator it2 = result2.first; it2 != result2.second; ++it2 )
    {
      xmlRow tmpRow;
      unsigned int i = 0; // we expect 6 necessary rows only

      // filter only cells, read all necessary data
      // reuse result
      result = it2->second.equal_range(nodeTableCell);
      for( ptree::const_assoc_iterator it3 = result.first; it3 != result.second; ++it3)
      {
        try
        {
          // filter cell that have value
          // sanity check, cell isn't empty
          it3->second.get_child(string(xmlattr) + "." + string(nodeOfficeValue));

          // get data from row
          // It is column number in ods table starting from 0
          // E.g. column A - cashflow, column B - source, e.t.c
          // It is suggested that column order is always the same as expected
          // for switch below.
          switch( i )
          {

            case 0:
              tmpRow.cashflow = it3->second.get<string>(string(nodeTableText));
              break;

            case 1:
              tmpRow.source = it3->second.get<string>(string(nodeTableText));
              break;

            case 2:
              tmpRow.dateP = from_string(it3->second.get<string>(string(nodeTableText)));
              break;

            case 3:
              tmpRow.item = it3->second.get<string>(string(nodeTableText));
              break;

            case 4:
              tmpRow.price = it3->second.get<float>(string(nodeTableText));
              break;

            case 5:
              tmpRow.amount = it3->second.get<float>(string(nodeTableText));
              break;

            default:
              cerr << __FILE__ << " " << __LINE__ << " " << __FUNCTION__ << endl
                   << "ERROR. Wrong column counter i = "<< i << endl;
          } // END switch

          // take this string into account only for successfull case
          ++i;

        }
        catch(const ptree_bad_path &e)
        {
          cerr << __FILE__ << " " << __LINE__ << " " << __FUNCTION__ << endl
               << "ERROR. No value in cell. Skip the hall row." << endl
               << "Error message: " << e.what() << endl;
          break;
        }
        catch(const bad_lexical_cast &e)
        {
          cerr << __FILE__ << " " << __LINE__ << " " << __FUNCTION__ << endl
               << "ERROR. Can't convert correctly value in cell. Skip the hall row." << endl
               << "Error message: " << e.what() << endl;
          break;
        }
        catch(...)
        {
          cerr << __FILE__ << " " << __LINE__ << " " << __FUNCTION__ << endl
               << "ERROR. Unknown error" << endl;
        }

      } // END for cells

//      cout << "DEBUG: " << endl << tmpRow << endl << endl;

      if( i != numCellsInRow )
      {
        cerr << __FILE__ << " " << __LINE__ << " " << __FUNCTION__ << endl
             << "ERROR. No necessary cells in row to fill the hall row. Skip this row."
             << " Cells = " << i << endl;
        continue;
      }
      else
      {
        // good row with all necessary cells
        table.push_back(tmpRow);
      } // END if

    } // END for rows

  } // END for table

  return table;
}


ContentReader::~ContentReader()
{
}
