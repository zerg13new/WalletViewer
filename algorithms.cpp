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
  ROUTINES
*/
static int safe_create_dir(const string &sPath);



vector<cashFlow> montlySimple(const vector<xmlRow> &data, date from, date to)
{

}


vector<cashFlow> yearlySimple(const vector<xmlRow> &data, date from, date to)
{

}


vector<cashFlow> mostExpensiveItems(const vector<xmlRow> &data, unsigned int numberofItemsToReturn)
{

}


ostream &operator <<(ostream &os, const xmlRow &row)
{
    os << "cashFlow: " << row.cashflow << endl
       << "source: " << row.source << endl
       << "dateP: " << to_iso_extended_string(row.dateP) << endl
       << "item: " << row.item << endl
       << "price: " << row.price << endl
       << "amount: " << row.amount;

    return os;
}


void sortDateSource(vector<xmlRow> &rows, const int sortOrder)
{
  if( 1 == sortOrder )
    sort(rows.begin(), rows.end(),[](xmlRow a, xmlRow b){
          return ( a.dateP != b.dateP ) ? (a.dateP < b.dateP) : (a.source < b.source);
        });
  else if( 2 == sortOrder )
    sort(rows.begin(), rows.end(),[](xmlRow a, xmlRow b){
          return ( a.dateP != b.dateP ) ? (a.dateP < b.dateP) : (a.source < b.source);
        });
  else
    cerr << __FILE__ << " " << __LINE__ << " " << __FUNCTION__ << endl
         << "ERROR: unknown order";
}


int extract_zip(const char *archive, const char *destination)
{
  const string ME_("extract_zip");
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
      cerr << ME_ << ": can't open zip archive " << archive
           << ", buf " << buf;
      return 1;
  }
 
  for(i = 0; i < zip_get_num_entries(za, 0); i++)
  {
    if( zip_stat_index(za, i, 0, &sb) )
    {
      cerr << ME_ << ": zip_stat_index failed" << endl;
    }
    else
    {
      /*
      cout << endl
           << "Name: " << sb.name << endl
           << "Size:" << sb.size << endl
           << "mtime: " << (unsigned int)sb.mtime
           << endl;
           */

      // create directory if it is necessary
      if( strstr(sb.name, "/") )
      {
        string tmpDir(destination);
        tmpDir.append("/").append(sb.name);

        if( safe_create_dir(tmpDir) )
          return 2;
      }
      else
      {
        zf = zip_fopen_index(za, i, 0);
        if(!zf)
        {
          cerr << ME_ << ": zip_fopen_index failed, zf = " << zf << endl;
          return 3;
        }

        string fullPathFileName(destination);
        fullPathFileName.append("/").append(sb.name);

        fd = open(fullPathFileName.c_str(), O_RDWR | O_TRUNC | O_CREAT, 0644);
        if(fd < 0)
        {
          cerr << ME_ << ": open file " << fullPathFileName.c_str()
               << " from archive " << archive << " failed, fd = " << fd << endl;
          return 4;
        }

        sum = 0;
        while(sum != sb.size)
        {
          len = zip_fread(zf, buf, 100);
          if(len < 0)
          {
            cerr << ME_ << ": zip_fread failed, len = " << len << endl;
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
    cerr << ME_ << ": can't close zip archive " << archive << endl;
    return 10;
  }

  return 0;
}

/**
 * @brief safe_create_dir is a function create absent directories in sPath
 * @param sPath path without trailed "/"
 * @return 0 for success or other positive value for failure
 */
static int safe_create_dir(const string &sPath)
{
  const string ME_ = "safe_create_dir";

  size_t          pos = 1;

  while( string::npos != (pos = sPath.find("/", pos)) )
  {
    string tmpPath(string(sPath, 0, pos));
    pos++;

    if(mkdir(tmpPath.c_str(), 0755) < 0)
    {
      if(errno != EEXIST)
      {
        cerr << ME_ << ": mkdir failed for " << tmpPath.c_str() << endl;
        return 1;
      }
    }

  }

    return 0;
}
