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


#ifndef _ODS_READER_H_
#define _ODS_READER_H_

#include <string>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>

#include "algorithms.h"

using std::string;
using std::runtime_error;
using boost::filesystem::path;
//using namespace boost::filesystem::detail;
using boost::filesystem::unique_path;
using boost::filesystem::temp_directory_path;
using boost::filesystem::current_path;
using boost::filesystem::exists;
using boost::filesystem::remove_all;

/**
 For reading content of *.ods file
*/
class ODSReader
{
  public:
    ODSReader(const string _odsFileName);
    virtual ~ODSReader();
    string getODSFileName() const;
    string getTmpDir() const;

  private:
    explicit ODSReader();
    explicit ODSReader(const ODSReader &obj);

    /**
      extract ods file
    */
    void extractFile();

  protected:
    string odsFileName;
    string tmpDir; // path (with trailed /) to tmpDir where *.ods file is placed
};

#endif
